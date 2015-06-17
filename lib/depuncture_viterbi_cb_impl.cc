/*
 * Copyright (c) 2010 Edmund Tse
 *               2015 Santiago Piccinini
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "depuncture_viterbi_cb_impl.h"

namespace gr {
  namespace dvb {
      

    static const std::vector<int> G(G_array, G_array + sizeof(G_array) / sizeof(int));
    static const gr::trellis::fsm f(k, n, G);
    static const std::vector<float> constellation(c_array, c_array + sizeof(c_array) / sizeof(float));


    depuncture_viterbi_cb::sptr
    depuncture_viterbi_cb::make(const std::vector<int> &sequence)
    {
      return gnuradio::get_initial_sptr
        (new depuncture_viterbi_cb_impl(sequence));
    }

    /*
     * The private constructor
     */
    depuncture_viterbi_cb_impl::depuncture_viterbi_cb_impl(const std::vector<int> &sequence)
      : gr::hier_block2("depuncture_viterbi_cb",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(unsigned char))),
        dropped(0),
        complex_adjust(gr::dvb::complex_adjust_cc::make()),	// Adjusts complex signal stream
        drop(gr::dvb::drop::make(sizeof(gr_complex))),		// Drops complex symbols for depuncture sync
        c2f(gr::dvb::complex_to_interleaved_float::make()),
        depuncture(gr::dvb::depuncture_ff::make(sequence)),	// 3/4 rate
        
        metrics(gr::trellis::metrics_f::make(f.O(), dimensionality, constellation, gr::digital::TRELLIS_EUCLIDEAN)),
        
        viterbi(gr::trellis::viterbi_b::make(f, K, -1, -1)),	// -1 for initial/final states not set
        sync_decoder(gr::dvb::sync_decoder::make())
    {
        assert(sequence.size() % 2 == 0);	// Expect an even number of items in the sequence (I/Q)
        assert(*std::max_element(sequence.begin(), sequence.end()) == 1);	// Puncturing matrix only has {0,1}

        unsigned int ones = std::count(sequence.begin(), sequence.end(), 1);
        alignment_boundaries = ones % 2 == 0 ? ones/2 : ones;

        // Set the sync decoder status callback function
        sync_decoder->set_status_callback(boost::bind(&depuncture_viterbi_cb_impl::sync_decoder_callback, this, _1));

        connect(self(), 0, complex_adjust, 0);
        connect(complex_adjust, 0, drop, 0);
        connect(drop, 0, c2f, 0);
        connect(c2f, 0, depuncture, 0);
        connect(depuncture, 0, metrics, 0);
        connect(metrics, 0, viterbi, 0);
        connect(viterbi, 0, sync_decoder, 0);
        connect(sync_decoder, 0, self(), 0);
    }
   /*
     * Our virtual destructor.
     */
    depuncture_viterbi_cb_impl::~depuncture_viterbi_cb_impl()
    {
    }
    

    void depuncture_viterbi_cb_impl::sync_decoder_callback(bool is_locked)
    {
        // This function is called by the sync decoder to let us know if the
        // parameters we are using to decode the stream is correct.
        if (!is_locked)
        {
            // Switch to the next combination of parameters
            next_alignment() && next_conj() && next_phase();
    /* Commented 19 Oct 10 - debugging purposes only
            std::cout << "Decoder input adjustment";
            std::cout << ": Phase " << complex_adjust->get_phase();
            std::cout << "; Conj " << complex_adjust->get_conj();
            std::cout << "; Depuncture alignment " << dropped << std::endl;
    */
        }
    }

    bool depuncture_viterbi_cb_impl::next_conj()
    {
        complex_adjust->set_conj(!complex_adjust->get_conj());
        return !complex_adjust->get_conj();
    }

    bool depuncture_viterbi_cb_impl::next_phase()
    {
        complex_adjust->set_phase((complex_adjust->get_phase() + 1) % 4);
        return complex_adjust->get_phase() == 0;
    }

    bool depuncture_viterbi_cb_impl::next_alignment()
    {
        drop->drop_next();
        dropped = (dropped + 1) % alignment_boundaries;
        return dropped == 0;
    }



  } /* namespace dvb */
} /* namespace gr */


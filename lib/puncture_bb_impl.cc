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
#include "puncture_bb_impl.h"

namespace gr {
  namespace dvb {

    puncture_bb::sptr
    puncture_bb::make(const std::vector<int> &sequence)
    {
      return gnuradio::get_initial_sptr
        (new puncture_bb_impl(sequence));
    }

    /*
     * The private constructor
     */
    puncture_bb_impl::puncture_bb_impl(const std::vector<int> &sequence)
      : gr::block("puncture_bb",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char))),
        index(0),
        nbits_keep(std::count(sequence.begin(), sequence.end(), 1)),
        nbits_total(sequence.size()),
        P(sequence)
    {}

    /*
     * Our virtual destructor.
     */
    puncture_bb_impl::~puncture_bb_impl()
    {
    }

    void
    puncture_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        // e.g. for 3/4 code, we need 4 bits input for every 3 bits punctured output
        std::fill(ninput_items_required.begin(), ninput_items_required.end(),
                noutput_items * nbits_total / nbits_keep);
    }

    int
    puncture_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const unsigned char *in = (const unsigned char *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];

        int ni = 0;
        int no = 0;

        // Terminate when we run out of either input data or output capacity
        while (ni < ninput_items[0] && no < noutput_items)
        {
            if (P[index] != 0)		// Not punctured, so copy across
            {
                out[no] = in[ni];
                ++no;
            }
            ++ni;
            index = (index + 1) % nbits_total;
        }

        consume_each(ni);
        return no;
    }

  } /* namespace dvb */
} /* namespace gr */


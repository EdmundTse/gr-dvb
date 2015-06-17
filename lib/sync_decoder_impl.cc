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
#include "sync_decoder_impl.h"

namespace gr {
  namespace dvb {

    sync_decoder::sptr
    sync_decoder::make()
    {
      return gnuradio::get_initial_sptr
        (new sync_decoder_impl());
    }

    /*
     * The private constructor
     */
    sync_decoder_impl::sync_decoder_impl()
      : gr::block("sync_decoder",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char))),
	bit_counter(0),
	status_callback(NULL) {}

    /*
     * Our virtual destructor.
     */
    sync_decoder_impl::~sync_decoder_impl()
    {
    }

    void
    sync_decoder_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        // For every output (packed) byte, we need at least 8 bits (unpacked)
        std::fill(ninput_items_required.begin(), ninput_items_required.end(), noutput_items * 8);
    }

    int
    sync_decoder_impl::general_work (int noutput_items,
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
            if (sync_search.process(in[ni]))	// True if output is triggered
            {
                out[no++] = sync_search.output();
            }

            assert(bit_counter >= 0);
            // Periodically callback to update sync status
            if (!status_callback.empty() && ++bit_counter == DWELL_DURATION)
            {
                bit_counter = 0;
                status_callback(sync_search.mode() != dvb_sync_search::Unlocked);
            }
            ++ni;
        }

        consume_each(ni);
        return no;
    }

  } /* namespace dvb */
} /* namespace gr */


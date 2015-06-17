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
#include "depuncture_ff_impl.h"

namespace gr {
  namespace dvb {

    depuncture_ff::sptr
    depuncture_ff::make(const std::vector<int> &sequence)
    {
      return gnuradio::get_initial_sptr
        (new depuncture_ff_impl(sequence));
    }

    /*
     * The private constructor
     */
    depuncture_ff_impl::depuncture_ff_impl(const gr_vector_int &sequence)
      : gr::block("depuncture_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))),
	index(0),
	P(sequence) {}

    /*
     * Our virtual destructor.
     */
    depuncture_ff_impl::~depuncture_ff_impl()
    {
    }

    void
    depuncture_ff_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        // Rather than giving a more exact estimate, we require the same number of input
        // items as output items to avoid requiring 0 input items
        std::fill(ninput_items_required.begin(), ninput_items_required.end(), noutput_items);
    }

    int
    depuncture_ff_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        float *out = (float *) output_items[0];

        int ni = 0;
        int no = 0;

        // Terminate when we run out of either input data or output capacity
        while (ni < ninput_items[0] && no < noutput_items)
        {
            if (P[index] != 0)		// Not punctured, so copy across
            {
                out[no] = in[ni];
                ++ni;
            }
            else					// Punctured, so insert a bit
            {
                out[no] = DVB_DEPUNCTURE_SYMBOL;
            }
            ++no;
            index = (index + 1) % P.size();
        }

        consume_each(ni);
        return no;
    }

  } /* namespace dvb */
} /* namespace gr */


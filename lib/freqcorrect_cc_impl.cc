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

#include <gnuradio/expj.h>
#include <gnuradio/io_signature.h>
#include "freqcorrect_cc_impl.h"

namespace gr {
  namespace dvb {

    freqcorrect_cc::sptr
    freqcorrect_cc::make(float alpha)
    {
      return gnuradio::get_initial_sptr
        (new freqcorrect_cc_impl(alpha));
    }

    /*
     * The private constructor
     */
    freqcorrect_cc_impl::freqcorrect_cc_impl(float alpha)
      : gr::sync_block("freqcorrect_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
        d_alpha(alpha), d_phase(0.0),
        d_sum(0.0), d_prev(0.0)
    {}

    /*
     * Our virtual destructor.
     */
    freqcorrect_cc_impl::~freqcorrect_cc_impl()
    {
    }

    int
    freqcorrect_cc_impl::work(int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

        for (int i = 0; i < noutput_items; ++i)
        {
            d_sum = d_sum * gr_complex(1.0 - d_alpha, 0.0) + gr_complex(d_alpha, 0.0) * (in[i] * d_prev);
            d_prev = std::conj(in[i]);
            d_phase -= std::arg(d_sum);

            while (d_phase > 2 * M_PI)
            {
                d_phase -= 2 * M_PI;
            }
            while (d_phase < -2 * M_PI)
            {
                d_phase += 2 * M_PI;
            }
            out[i] = in[i] * gr_expj(d_phase);
        }

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace dvb */
} /* namespace gr */

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
#include "complex_to_interleaved_float_impl.h"

namespace gr {
  namespace dvb {

    complex_to_interleaved_float::sptr
    complex_to_interleaved_float::make()
    {
      return gnuradio::get_initial_sptr
        (new complex_to_interleaved_float_impl());
    }

    /*
     * The private constructor
     */
    complex_to_interleaved_float_impl::complex_to_interleaved_float_impl()
      : gr::sync_interpolator("complex_to_interleaved_float",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float)),
              2)
    {}

    /*
     * Our virtual destructor.
     */
    complex_to_interleaved_float_impl::~complex_to_interleaved_float_impl()
    {
    }

    int
    complex_to_interleaved_float_impl::work(int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        float *out = (float *) output_items[0];

        for (int i = 0; i < noutput_items / 2; ++i)
        {
            *out++ = in[i].real();
            *out++ = in[i].imag();
        }

        return noutput_items;
    }

  } /* namespace dvb */
} /* namespace gr */


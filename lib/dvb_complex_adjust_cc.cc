/*
 * Copyright (c) 2010 Edmund Tse
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

#include "dvb_complex_adjust_cc.h"

// Define the four 90 degree phase rotations as complex multiplers
static const gr_complex phase[4] = { gr_complex(1), gr_complex(0,1), gr_complex(-1), gr_complex(0,-1) };

dvb_complex_adjust_cc_sptr dvb_make_complex_adjust_cc()
{
	return dvb_complex_adjust_cc_sptr(new dvb_complex_adjust_cc());
}

dvb_complex_adjust_cc::dvb_complex_adjust_cc()
	: gr_sync_block("complex_adjust_cc",
			gr_make_io_signature(1, 1, sizeof(gr_complex)),
			gr_make_io_signature(1, 1, sizeof(gr_complex))),
	conjugate(false),
	rotate_90(0) {}

int dvb_complex_adjust_cc::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const gr_complex *in = (const gr_complex *) input_items[0];
	gr_complex *out = (gr_complex *) output_items[0];

	// This inversion of checking conjugate flag first is for speed
	if (conjugate)
	{
		for (int i = 0; i < noutput_items; ++i)
		{
			out[i] = conj(in[i]) * phase[rotate_90];
		}
	}
	else
	{
		for (int i = 0; i < noutput_items; ++i)
		{
			out[i] = in[i] * phase[rotate_90];
		}
	}

	// Tell runtime system how many output items we produced.
	return noutput_items;
}

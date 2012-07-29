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

#ifndef INCLUDED_DVB_COMPLEX_TO_INTERLEAVED_FLOAT_H
#define INCLUDED_DVB_COMPLEX_TO_INTERLEAVED_FLOAT_H

#include <gr_io_signature.h>
#include <gr_sync_interpolator.h>

class dvb_complex_to_interleaved_float;
typedef boost::shared_ptr<dvb_complex_to_interleaved_float> dvb_complex_to_interleaved_float_sptr;
dvb_complex_to_interleaved_float_sptr dvb_make_complex_to_interleaved_float();

/*!
 * \brief Convert stream of complex to a stream of interleaved floats
 * \ingroup dvb
 */

class dvb_complex_to_interleaved_float : public gr_sync_interpolator
{
	private:
		dvb_complex_to_interleaved_float();

		friend dvb_complex_to_interleaved_float_sptr dvb_make_complex_to_interleaved_float();

	public:
		virtual int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
};

#endif /* INCLUDED_DVB_COMPLEX_TO_INTERLEAVED_FLOAT_H */

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

#include "dvb_fifo_shift_register_bb.h"

dvb_fifo_shift_register_bb_sptr dvb_make_fifo_shift_register_bb(size_t length)
{
	return dvb_fifo_shift_register_bb_sptr(new dvb_fifo_shift_register_bb(length));
}

dvb_fifo_shift_register_bb::dvb_fifo_shift_register_bb(size_t length)
	: gr_sync_block("fifo_shift_register_bb",
			gr_make_io_signature(1, 1, sizeof(unsigned char)),
			gr_make_io_signature(1, 1, sizeof(unsigned char))),
	index(0), buf_len(length), buffer(new unsigned char[length])
{
	// Initialise shift register to zeros
	std::fill(buffer, buffer + length, (unsigned char) 0);
}

dvb_fifo_shift_register_bb::~dvb_fifo_shift_register_bb()
{
	delete buffer;
}

int dvb_fifo_shift_register_bb::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const unsigned char *in = (const unsigned char *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];

	if (buf_len == 0)
	{
		for (int i = 0; i < noutput_items; ++i)
		{
			out[i] = in[i];
		}
	}
	else
	{
		for (int i = 0; i < noutput_items; ++i)
		{
			out[i] = buffer[index];
			buffer[index] = in[i];
			index = (index + 1) % buf_len;
		}
	}

	return noutput_items;
}

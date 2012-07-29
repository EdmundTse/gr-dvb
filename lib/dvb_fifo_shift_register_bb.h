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

#ifndef INCLUDED_DVB_FIFO_SHIFT_REGISTER_BB_H
#define INCLUDED_DVB_FIFO_SHIFT_REGISTER_BB_H

#include <algorithm>
#include <gr_io_signature.h>
#include <gr_sync_block.h>
#include "dvb_consts.h"

class dvb_fifo_shift_register_bb;
typedef boost::shared_ptr<dvb_fifo_shift_register_bb> dvb_fifo_shift_register_bb_sptr;
dvb_fifo_shift_register_bb_sptr dvb_make_fifo_shift_register_bb(size_t length);

/*!
 * \brief a FIFO shift register.
 * \ingroup block
 */
class dvb_fifo_shift_register_bb : public gr_sync_block
{
private:
	int index;				// Index of first element of circular buffer
	const size_t buf_len;	// Length of circular buffer
	unsigned char *buffer;	// Pointer to circular buffer
	dvb_fifo_shift_register_bb(size_t length);

	friend dvb_fifo_shift_register_bb_sptr dvb_make_fifo_shift_register_bb(size_t length);

 public:
	virtual ~dvb_fifo_shift_register_bb();

	int work(int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items);
};

#endif /* INCLUDED_DVB_FIFO_SHIFT_REGISTER_BB_H */

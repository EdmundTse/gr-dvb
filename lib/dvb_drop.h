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

#ifndef INCLUDED_DVB_DROP_H
#define INCLUDED_DVB_DROP_H

#include <algorithm>
#include <gr_io_signature.h>
#include <gr_block.h>

class dvb_drop;
typedef boost::shared_ptr<dvb_drop> dvb_drop_sptr;
dvb_drop_sptr dvb_make_drop(size_t item_size);

/*!
 * \brief
 * \ingroup dvb
 */
class dvb_drop : public gr_block
{
	private:
		volatile bool drop_next_item;
		dvb_drop(size_t item_size);

		friend dvb_drop_sptr dvb_make_drop(size_t item_size);

	public:
		virtual ~dvb_drop();

		// Estimates the number of input data items given a request to produce noutput_items
		void forecast(int noutput_items, gr_vector_int &ninput_items_required);

		// Compute output items from input items, and returns the number of items actually written
		// Must call consume or consume_each to indicate how many items were consumed on each input stream
		int general_work(int noutput_items,				// Number of output items to write on each output stream
				gr_vector_int &ninput_items,			// Number of input items available on each input stream
				gr_vector_const_void_star &input_items,	// Vector of pointers to the input items, 1 entry per stream
				gr_vector_void_star &output_items);		// Vector of pointers to the output items, 1 entry per stream

		//! Flag to drop the next item
		void drop_next();
};

#endif /* INCLUDED_DVB_DROP_H */

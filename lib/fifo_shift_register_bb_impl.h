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

#ifndef INCLUDED_DVB_FIFO_SHIFT_REGISTER_BB_IMPL_H
#define INCLUDED_DVB_FIFO_SHIFT_REGISTER_BB_IMPL_H

#include <dvb/fifo_shift_register_bb.h>
#include "dvb_consts.h"

namespace gr {
  namespace dvb {

    class fifo_shift_register_bb_impl : public fifo_shift_register_bb
    {
     private:
        int index;				// Index of first element of circular buffer
        const size_t buf_len;	// Length of circular buffer
        unsigned char *buffer;	// Pointer to circular buffer

     public:
      fifo_shift_register_bb_impl(size_t length);
      ~fifo_shift_register_bb_impl();

      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace dvb
} // namespace gr

#endif /* INCLUDED_DVB_FIFO_SHIFT_REGISTER_BB_IMPL_H */


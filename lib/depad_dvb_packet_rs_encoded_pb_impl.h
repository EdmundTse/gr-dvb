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

#ifndef INCLUDED_DVB_DEPAD_DVB_PACKET_RS_ENCODED_PB_IMPL_H
#define INCLUDED_DVB_DEPAD_DVB_PACKET_RS_ENCODED_PB_IMPL_H

#include <dvb/depad_dvb_packet_rs_encoded_pb.h>
#include "dvb_consts.h"
#include "dvb_types.h"

namespace gr {
  namespace dvb {

    class depad_dvb_packet_rs_encoded_pb_impl : public depad_dvb_packet_rs_encoded_pb
    {
     private:
      // Nothing to declare in this block.

     public:
      depad_dvb_packet_rs_encoded_pb_impl();
      ~depad_dvb_packet_rs_encoded_pb_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace dvb
} // namespace gr

#endif /* INCLUDED_DVB_DEPAD_DVB_PACKET_RS_ENCODED_PB_IMPL_H */


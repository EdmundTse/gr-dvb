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

#ifndef INCLUDED_DVB_RS_PP_H
#define INCLUDED_DVB_RS_PP_H

#include <cassert>
#include <gr_sync_block.h>
#include "dvb_types.h"
#include "dvb_rs_impl.h"

class dvb_rs_encoder_pp;
typedef boost::shared_ptr<dvb_rs_encoder_pp> dvb_rs_encoder_pp_sptr;
dvb_rs_encoder_pp_sptr dvb_make_rs_encoder_pp();

/*!
 * \brief Shortened Reed-Solomon (204,188) encoder for DVB
 * \ingroup dvb
 *
 * input: stream of mpeg_ts_packet
 * output: stream of dvb_packet_rs_encoded
 */
class dvb_rs_encoder_pp : public gr_sync_block
{
	private:
		dvb_rs reed_solomon;
		dvb_rs_encoder_pp();

		friend dvb_rs_encoder_pp_sptr dvb_make_rs_encoder_pp();

	public:
		~dvb_rs_encoder_pp() {}

		int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
};

// ------------------------------------------------------------------------

class dvb_rs_decoder_pp;
typedef boost::shared_ptr<dvb_rs_decoder_pp> dvb_rs_decoder_pp_sptr;
dvb_rs_decoder_pp_sptr dvb_make_rs_decoder_pp();

/*!
 * \brief Shortened Reed-Solomon (204,188) decoder for DVB
 * \ingroup dvb
 *
 * input: stream of dvb_packet_rs_encoded
 * output: stream of mpeg_ts_packet
 */
class dvb_rs_decoder_pp : public gr_sync_block
{
	private:
		dvb_rs reed_solomon;
		dvb_rs_decoder_pp();

		friend dvb_rs_decoder_pp_sptr dvb_make_rs_decoder_pp();

	public:
		~dvb_rs_decoder_pp() {}

		int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
};

#endif /* INCLUDED_DVB_RS_PP_H */

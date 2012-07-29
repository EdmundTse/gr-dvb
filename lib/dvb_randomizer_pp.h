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

#ifndef INCLUDED_DVB_RANDOMIZER_PP_H
#define INCLUDED_DVB_RANDOMIZER_PP_H

#include <cassert>
#include <cstring>

#include <gr_io_signature.h>
#include <gr_block.h>
#include <gr_sync_block.h>
#include "dvb_consts.h"
#include "dvb_types.h"
#include "dvb_randomizer_impl.h"

class dvb_randomizer_pp;
typedef boost::shared_ptr<dvb_randomizer_pp> dvb_randomizer_pp_sptr;
dvb_randomizer_pp_sptr dvb_make_randomizer_pp();

/*!
 * \brief DVB MPEG TS randomiser
 * \ingroup dvb
 *
 * Randomises a stream of MPEG TS packets for energy dispersal
 * input: stream of mpeg_ts_packet
 * output: stream of mpeg_ts_packet
 */
class dvb_randomizer_pp : public gr_sync_block
{
	private:
		dvb_randomizer randomizer;
		dvb_randomizer_pp();

		friend dvb_randomizer_pp_sptr dvb_make_randomizer_pp();

	public:
		virtual ~dvb_randomizer_pp() {}

		int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
};

// -----------------------------------------------------------------------------

class dvb_derandomizer_pp;
typedef boost::shared_ptr<dvb_derandomizer_pp> dvb_derandomizer_pp_sptr;
dvb_derandomizer_pp_sptr dvb_make_derandomizer_pp();

/*!
 * \brief DVB MPEG TS derandomizer
 * \ingroup dvb
 *
 * Derandomises a stream of randomised MPEG TS packets
 * input: mpeg_ts_packet
 * output: mpeg_ts_packet
 */
class dvb_derandomizer_pp : public gr_sync_block
{
	private:
		dvb_randomizer derandomizer;
		dvb_derandomizer_pp();

		friend dvb_derandomizer_pp_sptr dvb_make_derandomizer_pp();

	public:
		virtual ~dvb_derandomizer_pp() {}

		int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
};

#endif /* INCLUDED_DVB_RANDOMIZER_PP_H */

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

#include <gr_io_signature.h>
#include "dvb_rs_pp.h"

#include <iostream>

dvb_rs_encoder_pp_sptr dvb_make_rs_encoder_pp()
{
	return dvb_rs_encoder_pp_sptr(new dvb_rs_encoder_pp());
}

dvb_rs_encoder_pp::dvb_rs_encoder_pp()
	: gr_sync_block("dvb_rs_encoder_pp",
			gr_make_io_signature(1, 1, sizeof(mpeg_ts_packet)),
			gr_make_io_signature(1, 1, sizeof(dvb_packet_rs_encoded))) {}

int dvb_rs_encoder_pp::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const mpeg_ts_packet *in = (const mpeg_ts_packet *) input_items[0];
	dvb_packet_rs_encoded *out = (dvb_packet_rs_encoded *) output_items[0];

	for (int i = 0; i < noutput_items; ++i)
	{
		// Check sync byte
		assert(in[i].data[0] == MPEG_TS_SYNC_BYTE || in[i].data[0] == MPEG_TS_SYNC_BYTE_INV);

		reed_solomon.encode(out[i], in[i]);
	}

	// Tell runtime system how many output items we produced.
	return noutput_items;
}

// -----------------------------------------------------------------------------

dvb_rs_decoder_pp_sptr dvb_make_rs_decoder_pp()
{
	return dvb_rs_decoder_pp_sptr(new dvb_rs_decoder_pp());
}

dvb_rs_decoder_pp::dvb_rs_decoder_pp()
	: gr_sync_block("dvb_rs_decoder_pp",
			gr_make_io_signature(1, 1, sizeof(dvb_packet_rs_encoded)),
			gr_make_io_signature(1, 1, sizeof(mpeg_ts_packet))) {}

int dvb_rs_decoder_pp::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const dvb_packet_rs_encoded *in = (const dvb_packet_rs_encoded *) input_items[0];
	mpeg_ts_packet *out = (mpeg_ts_packet *) output_items[0];

	for (int i = 0; i < noutput_items; ++i)
	{
		if (reed_solomon.decode(out[i], in[i]) < 0)
		{
			// TODO: Pass this info down through some pipeline info
			std::cout << "RS: Uncorrectable error encountered." << std::endl;
		}
	}

	// Tell runtime system how many output items we produced.
	return noutput_items;
}

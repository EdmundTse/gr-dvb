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

#include "dvb_rs_impl.h"

dvb_rs::dvb_rs()
	: rs(init_rs_char(DVB_RS_SYMSIZE, DVB_RS_GFPOLY, DVB_RS_FCR, DVB_RS_PRIM, DVB_RS_NROOTS)) {}

dvb_rs::~dvb_rs()
{
	free_rs_char(rs);
}

void dvb_rs::encode(dvb_packet_rs_encoded &out, const mpeg_ts_packet &in)
{
	assert(sizeof(in.data) == MPEG_TS_PKT_LENGTH);
	unsigned char data[DVB_RS_PAD_LENGTH + MPEG_TS_PKT_LENGTH];

	// Shortened RS: prepend zero bytes to message (discarded after encoding)
	std::memset(data, 0, DVB_RS_PAD_LENGTH);
	std::memcpy(&data[DVB_RS_PAD_LENGTH], in.data, sizeof(in.data));

	// Copy input message to output then append RS bits
	std::memcpy(out.data, in.data, sizeof(in.data));
	encode_rs_char(rs, data, &out.data[sizeof(in.data)]);
}

int dvb_rs::decode(mpeg_ts_packet &out, const dvb_packet_rs_encoded &in)
{
	assert(sizeof(out.data) == MPEG_TS_PKT_LENGTH);
	unsigned char data[DVB_RS_PAD_LENGTH + DVB_RS_ENCODED_LENGTH];

	// Shortened RS: prepend zero bytes to message (discarded after encoding)
	std::memset(data, 0, DVB_RS_PAD_LENGTH);
	std::memcpy(&data[DVB_RS_PAD_LENGTH], in.data, sizeof(in.data));

	// Perform error correction then copy message to output
	int corrections = decode_rs_char(rs, data, 0, 0);	// No known erasures
	memcpy(out.data, &data[DVB_RS_PAD_LENGTH], sizeof(out.data));

	return corrections;
}

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

#ifndef INCLUDED_DVB_TYPES_H
#define INCLUDED_DVB_TYPES_H

#include <cstring>
#include "dvb_consts.h"

class plinfo
{
	protected:
		unsigned short _flags;		// Bitmask
		unsigned short _segno;		// Segment number

	public:
		plinfo();

		/*!
		 * Confirm that \p X is plausible
		 */
		static void sanity_check(const plinfo &in);

		// Getters
		
		/*!
		 * Set \p OUT such that it reflects a \p NSEGS_OF_DELAY
		 * pipeline delay from \p IN.
		 */
		static void delay(plinfo &out, const plinfo &in, int nsegs_of_delay);
		
		bool operator==(const plinfo &other) const;
		bool operator!=(const plinfo &other) const;
};

class mpeg_ts_packet
{
	public:
		static const size_t NPAD = 68;
		unsigned char data[MPEG_TS_PKT_LENGTH];
		unsigned char _pad[NPAD];				// Pad to a power of 2

		bool operator==(const mpeg_ts_packet &other) const;
		bool operator!=(const mpeg_ts_packet &other) const;
};

class dvb_packet_rs_encoded
{
	public:
		static const size_t NPAD = 52;
		unsigned char data[DVB_RS_ENCODED_LENGTH];
		unsigned char _pad[NPAD];				// Pad to a power of 2

		bool operator==(const dvb_packet_rs_encoded &other) const;
		bool operator!=(const dvb_packet_rs_encoded &other) const;
};

#endif /* INCLUDED_DVB_TYPES_H */

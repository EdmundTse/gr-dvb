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
#include "dvb_types.h"

plinfo::plinfo() {}

void plinfo::sanity_check(const plinfo&in) {}

void plinfo::delay(plinfo &out, const plinfo&in, int nsegs_of_delay) {}

bool plinfo::operator==(const plinfo &other) const
{
	return _flags == other._flags && _segno == other._segno;
}

bool plinfo::operator!=(const plinfo &other) const
{
	return !(_flags == other._flags && _segno == other._segno);
}

// -----------------------------------------------------------------------------

bool mpeg_ts_packet::operator==(const mpeg_ts_packet &other) const
{
	return std::memcmp(data, other.data, sizeof(data)) == 0;
}

bool mpeg_ts_packet::operator!=(const mpeg_ts_packet &other) const
{
	return !(std::memcmp(data, other.data, sizeof(data)) == 0);
}

// -----------------------------------------------------------------------------

bool dvb_packet_rs_encoded::operator==(const dvb_packet_rs_encoded &other) const
{
	return std::memcmp(data, other.data, sizeof(data)) == 0;
}

bool dvb_packet_rs_encoded::operator!=(const dvb_packet_rs_encoded &other) const
{
	return !(std::memcmp(data, other.data, sizeof(data)) == 0);
}

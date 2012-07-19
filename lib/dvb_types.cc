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

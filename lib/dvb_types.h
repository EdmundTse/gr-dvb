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

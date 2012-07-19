#ifndef INCLUDED_DVB_RANDOMIZER_IMPL_H
#define INCLUDED_DVB_RANDOMIZER_IMPL_H

#include <cassert>
#include "dvb_consts.h"
#include "dvb_types.h"

/*!
 * \brief DVB data randomiser implementation
 * \ingroup dvb
 */
class dvb_randomizer
{
	private:
		unsigned int counter;
		static const unsigned int PRELOAD_VALUE = 0x4a80;	// '100101010000000'
		unsigned char sequence[DVB_RANDOMIZER_PERIOD];		// The sequence to XOR with

		friend class qa_dvb_randomizer_pp;

	public:
		dvb_randomizer();
		virtual ~dvb_randomizer() {}

		//! Resets randomiser LFSR
		void reset();

		//! Whitens an MPEG TS packet
		void randomize(mpeg_ts_packet &out, const mpeg_ts_packet &in);
		//! De-whiten a randomised MPEG TS packet
		void derandomize(mpeg_ts_packet &out, const mpeg_ts_packet &in);
};

#endif /* INCLUDED_DVB_RANDOMIZER_IMPL_H */

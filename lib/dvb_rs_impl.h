#ifndef INCLUDED_DVB_RS_IMPL_H
#define INCLUDED_DVB_RS_IMPL_H

#include <cassert>
#include "dvb_consts.h"
#include "dvb_types.h"

extern "C"
{
	#include <rs.h>
}

/*!
 * \brief DVB Reed-Solomon encoder/decoder
 *
 * RS(204,188,T=8) shortened code.
 */
class dvb_rs
{
	private:
		void *rs;		// RS characteristics structure

	public:
		dvb_rs();
		~dvb_rs();

		/*!
		 * \brief Add RS error correction encoding
		 */
		void encode(dvb_packet_rs_encoded &out, const mpeg_ts_packet &in);

		/*!
		 * \brief Decodes RS encoded packet.
		 * \returns a count of corrected symbols, or -1 if the block was uncorrectible.
		 */
		int decode(mpeg_ts_packet &out, const dvb_packet_rs_encoded &in);
};

#endif /* INCLUDED_DVB_RS_IMPL_H */

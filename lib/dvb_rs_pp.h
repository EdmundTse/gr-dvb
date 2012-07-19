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

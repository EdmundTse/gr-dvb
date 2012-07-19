#ifndef INCLUDED_DVB_PAD_H
#define INCLUDED_DVB_PAD_H

#include <cstring>

#include <gr_io_signature.h>
#include <gr_sync_decimator.h>
#include <gr_sync_interpolator.h>
#include "dvb_consts.h"
#include "dvb_types.h"

// -----------------------------------------------------------------------------

class dvb_pad_mpeg_ts_packet_bp;
typedef boost::shared_ptr<dvb_pad_mpeg_ts_packet_bp> dvb_pad_mpeg_ts_packet_bp_sptr;
dvb_pad_mpeg_ts_packet_bp_sptr dvb_make_pad_mpeg_ts_packet_bp();

/*!
 * \brief Pads MPEG TS packets from 188 bytes to 256 bytes to fit sizeof_mpeg_ts_packet
 * \ingroup dvb
 *
 * input: unsigned char
 * output: mpeg_ts_packet
 */
class dvb_pad_mpeg_ts_packet_bp : public gr_sync_decimator
{
	private:
		dvb_pad_mpeg_ts_packet_bp();

		friend dvb_pad_mpeg_ts_packet_bp_sptr dvb_make_pad_mpeg_ts_packet_bp();

	public:
		virtual ~dvb_pad_mpeg_ts_packet_bp();

		void forecast(int noutput_items, gr_vector_int &ninput_items_required);
		int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
		void reset();
};

// -----------------------------------------------------------------------------

class dvb_depad_mpeg_ts_packet_pb;
typedef boost::shared_ptr<dvb_depad_mpeg_ts_packet_pb> dvb_depad_mpeg_ts_packet_pb_sptr;
dvb_depad_mpeg_ts_packet_pb_sptr dvb_make_depad_mpeg_ts_packet_pb();

/*!
 * \brief De-pads MPEG TS packets from 256 bytes sizeof_mpeg_ts_packet back to 188 bytes
 * \ingroup dvb
 *
 * input: mpeg_ts_packet
 * output: unsigned char
 */
class dvb_depad_mpeg_ts_packet_pb : public gr_sync_interpolator
{
	private:
		dvb_depad_mpeg_ts_packet_pb();

		friend dvb_depad_mpeg_ts_packet_pb_sptr dvb_make_depad_mpeg_ts_packet_pb();

	public:
		virtual ~dvb_depad_mpeg_ts_packet_pb();

		int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
		void reset();
};

// -----------------------------------------------------------------------------

class dvb_pad_dvb_packet_rs_encoded_bp;
typedef boost::shared_ptr<dvb_pad_dvb_packet_rs_encoded_bp> dvb_pad_dvb_packet_rs_encoded_bp_sptr;
dvb_pad_dvb_packet_rs_encoded_bp_sptr dvb_make_pad_dvb_packet_rs_encoded_bp();

/*!
 * \brief Pads RS protected packets from 204 bytes to 256 bytes to fit sizeof_dvb_packet_rs_encoded
 * \ingroup dvb
 *
 * input: unsigned char
 * output: dvb_packet_rs_encoded
 */
class dvb_pad_dvb_packet_rs_encoded_bp : public gr_sync_decimator
{
	private:
		dvb_pad_dvb_packet_rs_encoded_bp();

		friend dvb_pad_dvb_packet_rs_encoded_bp_sptr dvb_make_pad_dvb_packet_rs_encoded_bp();

	public:
		virtual ~dvb_pad_dvb_packet_rs_encoded_bp();

		void forecast(int noutput_items, gr_vector_int &ninput_items_required);
		int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
		void reset();
};

// -----------------------------------------------------------------------------

class dvb_depad_dvb_packet_rs_encoded_pb;
typedef boost::shared_ptr<dvb_depad_dvb_packet_rs_encoded_pb> dvb_depad_dvb_packet_rs_encoded_pb_sptr;
dvb_depad_dvb_packet_rs_encoded_pb_sptr dvb_make_depad_dvb_packet_rs_encoded_pb();

/*!
 * \brief De-pads RS protected packets from 256 bytes back to 204 bytes
 * \ingroup dvb
 *
 * input: dvb_packet_rs_encoded
 * output: unsigned char
 */
class dvb_depad_dvb_packet_rs_encoded_pb : public gr_sync_interpolator
{
	private:
		dvb_depad_dvb_packet_rs_encoded_pb();

		friend dvb_depad_dvb_packet_rs_encoded_pb_sptr dvb_make_depad_dvb_packet_rs_encoded_pb();

	public:
		virtual ~dvb_depad_dvb_packet_rs_encoded_pb();

		int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
		void reset();
};
#endif /* INCLUDED_DVB_PAD_H */

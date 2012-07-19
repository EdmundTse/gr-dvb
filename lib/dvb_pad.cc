#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "dvb_pad.h"

dvb_pad_mpeg_ts_packet_bp_sptr dvb_make_pad_mpeg_ts_packet_bp()
{
	return dvb_pad_mpeg_ts_packet_bp_sptr(new dvb_pad_mpeg_ts_packet_bp());
}

dvb_pad_mpeg_ts_packet_bp::dvb_pad_mpeg_ts_packet_bp()
	: gr_sync_decimator("dvb_pad_mpeg_ts_packet_bp",
			gr_make_io_signature(1, 1, sizeof(unsigned char)),
			gr_make_io_signature(1, 1, sizeof(mpeg_ts_packet)),
			MPEG_TS_PKT_LENGTH)
{
	reset();
}

dvb_pad_mpeg_ts_packet_bp::~dvb_pad_mpeg_ts_packet_bp() {}

void dvb_pad_mpeg_ts_packet_bp::reset() {}

void dvb_pad_mpeg_ts_packet_bp::forecast(int noutput_items, gr_vector_int &ninput_items_required)
{
	unsigned ninputs = ninput_items_required.size();
	for (unsigned i = 0; i < ninputs; ++i)
	{
		ninput_items_required[i] = noutput_items * MPEG_TS_PKT_LENGTH;

	}
}

int dvb_pad_mpeg_ts_packet_bp::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const unsigned char *in = (const unsigned char *) input_items[0];
	mpeg_ts_packet *out = (mpeg_ts_packet *) output_items[0];

	for (int i = 0; i < noutput_items; ++i)
	{
		std::memcpy(out[i].data, &in[i * MPEG_TS_PKT_LENGTH], MPEG_TS_PKT_LENGTH);
	}

	return noutput_items;
}

// -----------------------------------------------------------------------------

dvb_depad_mpeg_ts_packet_pb_sptr dvb_make_depad_mpeg_ts_packet_pb()
{
	return dvb_depad_mpeg_ts_packet_pb_sptr(new dvb_depad_mpeg_ts_packet_pb());
}

dvb_depad_mpeg_ts_packet_pb::dvb_depad_mpeg_ts_packet_pb()
	: gr_sync_interpolator("dvb_depad_mpeg_ts_packet_pb",
			gr_make_io_signature(1, 1, sizeof(mpeg_ts_packet)),
			gr_make_io_signature(1, 1, sizeof(unsigned char)),
			MPEG_TS_PKT_LENGTH)
{
	reset();
}

dvb_depad_mpeg_ts_packet_pb::~dvb_depad_mpeg_ts_packet_pb() {}

void dvb_depad_mpeg_ts_packet_pb::reset() {}

int dvb_depad_mpeg_ts_packet_pb::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const mpeg_ts_packet *in = (const mpeg_ts_packet *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];

	for (int i = 0; i < noutput_items / MPEG_TS_PKT_LENGTH; ++i)
	{
		std::memcpy(&out[i * MPEG_TS_PKT_LENGTH], in[i].data, MPEG_TS_PKT_LENGTH);
	}

	return noutput_items;
}

// -----------------------------------------------------------------------------

dvb_pad_dvb_packet_rs_encoded_bp_sptr dvb_make_pad_dvb_packet_rs_encoded_bp()
{
	return dvb_pad_dvb_packet_rs_encoded_bp_sptr(new dvb_pad_dvb_packet_rs_encoded_bp());
}

dvb_pad_dvb_packet_rs_encoded_bp::dvb_pad_dvb_packet_rs_encoded_bp()
	: gr_sync_decimator("dvb_pad_dvb_packet_rs_encoded_bp",
			gr_make_io_signature(1, 1, sizeof(unsigned char)),
			gr_make_io_signature(1, 1, sizeof(dvb_packet_rs_encoded)),
			DVB_RS_ENCODED_LENGTH)
{
	reset();
}

dvb_pad_dvb_packet_rs_encoded_bp::~dvb_pad_dvb_packet_rs_encoded_bp() {}

void dvb_pad_dvb_packet_rs_encoded_bp::reset() {}

void dvb_pad_dvb_packet_rs_encoded_bp::forecast(int noutput_items, gr_vector_int &ninput_items_required)
{
	unsigned ninputs = ninput_items_required.size();
	for (unsigned i = 0; i < ninputs; ++i)
	{
		ninput_items_required[i] = noutput_items * DVB_RS_ENCODED_LENGTH;
	}
}

int dvb_pad_dvb_packet_rs_encoded_bp::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const unsigned char *in = (const unsigned char *) input_items[0];
	dvb_packet_rs_encoded *out = (dvb_packet_rs_encoded *) output_items[0];

	for (int i = 0; i < noutput_items; ++i)
	{
		std::memcpy(out[i].data, &in[i * DVB_RS_ENCODED_LENGTH], DVB_RS_ENCODED_LENGTH);
	}

	return noutput_items;
}

// -----------------------------------------------------------------------------

dvb_depad_dvb_packet_rs_encoded_pb_sptr dvb_make_depad_dvb_packet_rs_encoded_pb()
{
	return dvb_depad_dvb_packet_rs_encoded_pb_sptr(new dvb_depad_dvb_packet_rs_encoded_pb());
}

dvb_depad_dvb_packet_rs_encoded_pb::dvb_depad_dvb_packet_rs_encoded_pb()
	: gr_sync_interpolator("dvb_depad_dvb_packet_rs_encoded_pb",
			gr_make_io_signature(1, 1, sizeof(dvb_packet_rs_encoded)),
			gr_make_io_signature(1, 1, sizeof(unsigned char)),
			DVB_RS_ENCODED_LENGTH)
{
	reset();
}

dvb_depad_dvb_packet_rs_encoded_pb::~dvb_depad_dvb_packet_rs_encoded_pb() {}

void dvb_depad_dvb_packet_rs_encoded_pb::reset() {}

int dvb_depad_dvb_packet_rs_encoded_pb::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const dvb_packet_rs_encoded *in = (const dvb_packet_rs_encoded *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];

	for (int i = 0; i < noutput_items / DVB_RS_ENCODED_LENGTH; ++i)
	{
		std::memcpy(&out[i * DVB_RS_ENCODED_LENGTH], in[i].data, DVB_RS_ENCODED_LENGTH);
	}

	return noutput_items;
}

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "dvb_randomizer_pp.h"

dvb_randomizer_pp_sptr dvb_make_randomizer_pp()
{
	return dvb_randomizer_pp_sptr(new dvb_randomizer_pp());
}

dvb_randomizer_pp::dvb_randomizer_pp()
	: gr_sync_block("randomizer_pp",
			gr_make_io_signature(1, 1, sizeof(mpeg_ts_packet)),
			gr_make_io_signature(1, 1, sizeof(mpeg_ts_packet))) {}

int dvb_randomizer_pp::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const mpeg_ts_packet *in = (const mpeg_ts_packet *) input_items[0];
	mpeg_ts_packet *out = (mpeg_ts_packet *) output_items[0];

	for (int i = 0; i < noutput_items; ++i)
	{
		// Sanity check on incoming data
		assert(in[i].data[0] == MPEG_TS_SYNC_BYTE);
		assert((in[i].data[1] & MPEG_TS_ERROR_BIT) == 0);

		randomizer.randomize(out[i], in[i]);
	}

	// Tell runtime system how many output items we produced.
	return noutput_items;
}

// -----------------------------------------------------------------------------

dvb_derandomizer_pp_sptr dvb_make_derandomizer_pp()
{
	return dvb_derandomizer_pp_sptr(new dvb_derandomizer_pp());
}

dvb_derandomizer_pp::dvb_derandomizer_pp()
	: gr_sync_block("derandomizer_pp",
			gr_make_io_signature(1, 1, sizeof(mpeg_ts_packet)),
			gr_make_io_signature(1, 1, sizeof(mpeg_ts_packet))) {}

int dvb_derandomizer_pp::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const mpeg_ts_packet *in = (const mpeg_ts_packet *) input_items[0];
	mpeg_ts_packet *out = (mpeg_ts_packet *) output_items[0];

	for (int i = 0; i < noutput_items; ++i)
	{
		derandomizer.derandomize(out[i], in[i]);
	}

	// Tell runtime system how many output items we produced.
	return noutput_items;
}

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "dvb_sync_decoder.h"

dvb_sync_decoder_sptr dvb_make_sync_decoder()
{
	return dvb_sync_decoder_sptr(new dvb_sync_decoder());
}

dvb_sync_decoder::dvb_sync_decoder()
	: gr_block("dvb_sync_decoder",
			gr_make_io_signature(1, 1, sizeof(unsigned char)),
			gr_make_io_signature(1, 1, sizeof(unsigned char))),
	bit_counter(0),
	status_callback(NULL) {}

dvb_sync_decoder::~dvb_sync_decoder() {}

void dvb_sync_decoder::forecast(int noutput_items, gr_vector_int &ninput_items_required)
{
	// For every output (packed) byte, we need at least 8 bits (unpacked)
	std::fill(ninput_items_required.begin(), ninput_items_required.end(), noutput_items * 8);
}

int dvb_sync_decoder::general_work(int noutput_items,
		gr_vector_int &ninput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const unsigned char *in = (const unsigned char *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];

	int ni = 0;
	int no = 0;

	// Terminate when we run out of either input data or output capacity
	while (ni < ninput_items[0] && no < noutput_items)
	{	
		if (sync_search.process(in[ni]))	// True if output is triggered
		{
			out[no++] = sync_search.output();
		}

		assert(bit_counter >= 0);
		// Periodically callback to update sync status
		if (!status_callback.empty() && ++bit_counter == DWELL_DURATION)
		{
			bit_counter = 0;
			status_callback(sync_search.mode() != dvb_sync_search::Unlocked);
		}
		++ni;
	}

	consume_each(ni);
	return no;
}

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "dvb_drop.h"

dvb_drop_sptr dvb_make_drop(size_t item_size)
{
	return dvb_drop_sptr(new dvb_drop(item_size));
}

dvb_drop::dvb_drop(size_t item_size)
	: gr_block("dvb_drop",
			gr_make_io_signature(1, 1, item_size),
			gr_make_io_signature(1, 1, item_size)),
	drop_next_item(false) {}

dvb_drop::~dvb_drop() {}

void dvb_drop::forecast(int noutput_items, gr_vector_int &ninput_items_required)
{
	// We don't know how often we'd need to drop, we estimate 1 item needed per output
	std::fill(ninput_items_required.begin(), ninput_items_required.end(), noutput_items);
}

int dvb_drop::general_work(int noutput_items,
		gr_vector_int &ninput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const unsigned char *in = (const unsigned char *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];

	size_t item_size = input_signature()->sizeof_stream_item(0);
	int ni = 0;
	int no = 0;

	// Terminate when we run out of either input data or output capacity
	while (ni < ninput_items[0] && no < noutput_items)
	{
		if (drop_next_item)
		{
			drop_next_item = false;
		}
		else
		{
			std::memcpy(out, in, item_size);
			out += item_size;
			++no;
		}
		in += item_size;
		++ni;
	}

	consume_each(ni);
	return no;
}

void dvb_drop::drop_next()
{
	drop_next_item = true;
}

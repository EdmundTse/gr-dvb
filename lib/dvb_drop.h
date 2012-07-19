#ifndef INCLUDED_DVB_DROP_H
#define INCLUDED_DVB_DROP_H

#include <algorithm>
#include <gr_io_signature.h>
#include <gr_block.h>

class dvb_drop;
typedef boost::shared_ptr<dvb_drop> dvb_drop_sptr;
dvb_drop_sptr dvb_make_drop(size_t item_size);

/*!
 * \brief
 * \ingroup dvb
 */
class dvb_drop : public gr_block
{
	private:
		volatile bool drop_next_item;
		dvb_drop(size_t item_size);

		friend dvb_drop_sptr dvb_make_drop(size_t item_size);

	public:
		virtual ~dvb_drop();

		// Estimates the number of input data items given a request to produce noutput_items
		void forecast(int noutput_items, gr_vector_int &ninput_items_required);

		// Compute output items from input items, and returns the number of items actually written
		// Must call consume or consume_each to indicate how many items were consumed on each input stream
		int general_work(int noutput_items,				// Number of output items to write on each output stream
				gr_vector_int &ninput_items,			// Number of input items available on each input stream
				gr_vector_const_void_star &input_items,	// Vector of pointers to the input items, 1 entry per stream
				gr_vector_void_star &output_items);		// Vector of pointers to the output items, 1 entry per stream

		//! Flag to drop the next item
		void drop_next();
};

#endif /* INCLUDED_DVB_DROP_H */

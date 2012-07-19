#ifndef INCLUDED_DVB_PUNCTURE_H
#define INCLUDED_DVB_PUNCTURE_H

#include <algorithm>
#include <gr_io_signature.h>
#include <gr_block.h>
#include "dvb_consts.h"

class dvb_puncture_bb;
typedef boost::shared_ptr<dvb_puncture_bb> dvb_puncture_bb_sptr;
dvb_puncture_bb_sptr dvb_make_puncture_bb(gr_vector_int sequence);

/*!
 * \brief Puctures a stream of unpacked bytes by dropping according to sequence
 * \ingroup dvb
 *
 * input: unsigned char (unpacked 1 bit per byte)
 * output: unsigned char (unpacked 1 bit per byte)
 */
class dvb_puncture_bb : public gr_block
{
	private:
		unsigned int index;
		unsigned int nbits_keep;	// Number of bits to keep
		unsigned int nbits_total;	// Number of bits in puncturing sequence
		const gr_vector_int P;
		dvb_puncture_bb(gr_vector_int sequence);

		friend dvb_puncture_bb_sptr dvb_make_puncture_bb(gr_vector_int sequence);

	public:
		virtual ~dvb_puncture_bb() {}

		// Estimates the number of input data items given a request to produce noutput_items
		void forecast(int noutput_items, gr_vector_int &ninput_items_required);

		// Compute output items from input items, and returns the number of items actually written
		// Must call consume or consume_each to indicate how many items were consumed on each input stream
		int general_work(int noutput_items,				// Number of output items to write on each output stream
				gr_vector_int &ninput_items,			// Number of input items available on each input stream
				gr_vector_const_void_star &input_items,	// Vector of pointers to the input items, 1 entry per stream
				gr_vector_void_star &output_items);		// Vector of pointers to the output items, 1 entry per stream
};

// -----------------------------------------------------------------------------

class dvb_depuncture_ff;
typedef boost::shared_ptr<dvb_depuncture_ff> dvb_depuncture_ff_sptr;
dvb_depuncture_ff_sptr dvb_make_depuncture_ff(gr_vector_int sequence);

/*!
 * \brief Depuctures a stream by inserting according to sequence
 * \ingroup dvb
 */
class dvb_depuncture_ff : public gr_block
{
	private:
		unsigned int index;
		const gr_vector_int P;
		dvb_depuncture_ff(gr_vector_int sequence);

		friend dvb_depuncture_ff_sptr dvb_make_depuncture_ff(gr_vector_int sequence);

	public:
		virtual ~dvb_depuncture_ff() {}

		// Estimates the number of input data items given a request to produce noutput_items
		void forecast(int noutput_items, gr_vector_int &ninput_items_required);

		// Compute output items from input items, and returns the number of items actually written
		// Must call consume or consume_each to indicate how many items were consumed on each input stream
		int general_work(int noutput_items,				// Number of output items to write on each output stream
				gr_vector_int &ninput_items,			// Number of input items available on each input stream
				gr_vector_const_void_star &input_items,	// Vector of pointers to the input items, 1 entry per stream
				gr_vector_void_star &output_items);		// Vector of pointers to the output items, 1 entry per stream
};

#endif /* INCLUDED_DVB_PUNCTURE_H */

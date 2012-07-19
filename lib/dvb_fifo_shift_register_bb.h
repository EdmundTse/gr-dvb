#ifndef INCLUDED_DVB_FIFO_SHIFT_REGISTER_BB_H
#define INCLUDED_DVB_FIFO_SHIFT_REGISTER_BB_H

#include <algorithm>
#include <gr_io_signature.h>
#include <gr_sync_block.h>
#include "dvb_consts.h"

class dvb_fifo_shift_register_bb;
typedef boost::shared_ptr<dvb_fifo_shift_register_bb> dvb_fifo_shift_register_bb_sptr;
dvb_fifo_shift_register_bb_sptr dvb_make_fifo_shift_register_bb(size_t length);

/*!
 * \brief a FIFO shift register.
 * \ingroup block
 */
class dvb_fifo_shift_register_bb : public gr_sync_block
{
private:
	int index;				// Index of first element of circular buffer
	const size_t buf_len;	// Length of circular buffer
	unsigned char *buffer;	// Pointer to circular buffer
	dvb_fifo_shift_register_bb(size_t length);

	friend dvb_fifo_shift_register_bb_sptr dvb_make_fifo_shift_register_bb(size_t length);

 public:
	virtual ~dvb_fifo_shift_register_bb();

	int work(int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items);
};

#endif /* INCLUDED_DVB_FIFO_SHIFT_REGISTER_BB_H */

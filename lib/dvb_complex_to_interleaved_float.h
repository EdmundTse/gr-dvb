#ifndef INCLUDED_DVB_COMPLEX_TO_INTERLEAVED_FLOAT_H
#define INCLUDED_DVB_COMPLEX_TO_INTERLEAVED_FLOAT_H

#include <gr_io_signature.h>
#include <gr_sync_interpolator.h>

class dvb_complex_to_interleaved_float;
typedef boost::shared_ptr<dvb_complex_to_interleaved_float> dvb_complex_to_interleaved_float_sptr;
dvb_complex_to_interleaved_float_sptr dvb_make_complex_to_interleaved_float();

/*!
 * \brief Convert stream of complex to a stream of interleaved floats
 * \ingroup dvb
 */

class dvb_complex_to_interleaved_float : public gr_sync_interpolator
{
	private:
		dvb_complex_to_interleaved_float();

		friend dvb_complex_to_interleaved_float_sptr dvb_make_complex_to_interleaved_float();

	public:
		virtual int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
};

#endif /* INCLUDED_DVB_COMPLEX_TO_INTERLEAVED_FLOAT_H */

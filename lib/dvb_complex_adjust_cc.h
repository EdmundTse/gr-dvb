#ifndef INCLUDED_DVB_COMPLEX_ADJUST_CC_H
#define INCLUDED_DVB_COMPLEX_ADJUST_CC_H

#include <cassert>
#include <gr_complex.h>
#include <gr_io_signature.h>
#include <gr_sync_block.h>

class dvb_complex_adjust_cc;
typedef boost::shared_ptr<dvb_complex_adjust_cc> dvb_complex_adjust_cc_sptr;
dvb_complex_adjust_cc_sptr dvb_make_complex_adjust_cc();

/*!
 * \brief Applies conjugation and/or phase rotations to a complex stream
 * \ingroup dvb
 */
class dvb_complex_adjust_cc : public gr_sync_block
{
	private:
		volatile bool conjugate;		// Correct complex conjugate ambiguity
		volatile int rotate_90;			// Correct 90 degree phase ambiguity
		dvb_complex_adjust_cc();

		friend dvb_complex_adjust_cc_sptr dvb_make_complex_adjust_cc();

	public:
		virtual ~dvb_complex_adjust_cc() {}

		int work(int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);

		inline bool get_conj() const { return conjugate; }
		inline void set_conj(const bool c) { conjugate = c; }

		inline int get_phase() const { return rotate_90; }
		inline void set_phase(const int rotations)
		{
			rotate_90 = rotations % 4;
		}
};

#endif /* INCLUDED_DVB_COMPLEX_ADJUST_CC_H */

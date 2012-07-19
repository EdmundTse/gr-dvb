#ifndef INCLUDED_FREQCORRECT_CC_H
#define INCLUDED_FREQCORRECT_CC_H

#include <gr_complex.h>
#include <gr_expj.h>
#include <gr_io_signature.h>
#include <gr_math.h>
#include <gr_sync_block.h>

class dvb_freqcorrect_cc;
typedef boost::shared_ptr<dvb_freqcorrect_cc> dvb_freqcorrect_cc_sptr;
dvb_freqcorrect_cc_sptr dvb_make_freqcorrect_cc(float alpha);

/*!
 * \brief Performs frequency drift correction for a coherently decoded signal
 * \ingroup dvb
 */
class dvb_freqcorrect_cc : public gr_sync_block
{
	private:
		float d_alpha, d_phase;
		gr_complex d_sum, d_prev;
		dvb_freqcorrect_cc(float alpha);
		friend dvb_freqcorrect_cc_sptr dvb_make_freqcorrect_cc(float alpha);

	public:
		virtual ~dvb_freqcorrect_cc() {}

		int work (int noutput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items);
};

#endif /* INCLUDED_FREQCORRECT_CC_H */

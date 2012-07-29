/*
 * Copyright (c) 2010 Edmund Tse
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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

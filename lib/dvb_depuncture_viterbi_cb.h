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

#ifndef INCLUDED_DVB_DEPUNCTURE_VITERBI_CB_H
#define INCLUDED_DVB_DEPUNCTURE_VITERBI_CB_H

#include <algorithm>
#include <cassert>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <gnuradio/fsm.h>
#include <gnuradio/gr_complex_to_xxx.h>
#include <gnuradio/gr_interleave.h>
#include <gnuradio/trellis_metrics_f.h>
#include <gnuradio/trellis_viterbi_b.h>
#include <gr_hier_block2.h>
#include <gr_io_signature.h>
#include "dvb_complex_adjust_cc.h"
#include "dvb_complex_to_interleaved_float.h"
#include "dvb_drop.h"
#include "dvb_puncture.h"
#include "dvb_sync_decoder.h"

class dvb_depuncture_viterbi_cb;
typedef boost::shared_ptr<dvb_depuncture_viterbi_cb> dvb_depuncture_viterbi_cb_sptr;
dvb_depuncture_viterbi_cb_sptr dvb_make_depuncture_viterbi_cb(gr_vector_int sequence);

/*!
 * \brief Performs depuncturing and Viterbi decoding
 * \ingroup dvb
 *
 * Performs depuncturing and Viterbi decoding, then synchronises to MPEG TS
 * sync bytes before outputting packed bytes starting from the first
 * inverted SYNC byte after reaching synchronisation.
 *
 * input: gr_complex demodulated symbols
 * output: unsigned char
 */
class dvb_depuncture_viterbi_cb : public gr_hier_block2
{
	private:
		dvb_depuncture_viterbi_cb(gr_vector_int sequence);
		friend dvb_depuncture_viterbi_cb_sptr dvb_make_depuncture_viterbi_cb(gr_vector_int sequence);
		unsigned int dropped;
		unsigned int alignment_boundaries;

		bool next_conj();
		bool next_phase();
		bool next_alignment();

		// Sub blocks
		dvb_complex_adjust_cc_sptr complex_adjust;
		dvb_drop_sptr drop;
		dvb_complex_to_interleaved_float_sptr c2f;
		dvb_depuncture_ff_sptr depuncture;
		trellis_metrics_f_sptr metrics;
		trellis_viterbi_b_sptr viterbi;
		dvb_sync_decoder_sptr sync_decoder;

	public:
		// Callback to signal whether or not the current parameters are correct
		void sync_decoder_callback(bool is_locked);
};

#endif /* INCLUDED_DVB_DEPUNCTURE_VITERBI_CB_H */

/* -*- c++ -*- */

%include "gnuradio.i"			// the common stuff

%{
#include "dvb_types.h"
#include "dvb_pad.h"
#include "dvb_complex_to_interleaved_float.h"
#include "dvb_complex_adjust_cc.h"
#include "dvb_drop.h"
#include "dvb_fifo_shift_register_bb.h"
#include "dvb_freqcorrect_cc.h"
#include "dvb_puncture.h"
#include "dvb_rs_pp.h"
#include "dvb_randomizer_pp.h"
#include "dvb_sync_decoder.h"
#include "dvb_depuncture_viterbi_cb.h"
%}

%include "../lib/dvb_consts.h"

%include "dvb_types.i"
%include "dvb_pad.i"
%include "dvb_complex_to_interleaved_float.i"
%include "dvb_complex_adjust_cc.i"
%include "dvb_drop.i"
%include "dvb_fifo_shift_register_bb.i"
%include "dvb_freqcorrect_cc.i"
%include "dvb_puncture.i"
%include "dvb_rs_pp.i"
%include "dvb_randomizer_pp.i"
%include "dvb_sync_decoder.i"
%include "dvb_depuncture_viterbi_cb.i"

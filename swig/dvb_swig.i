/* -*- c++ -*- */

#define DVB_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "dvb_swig_doc.i"

%{
#include "dvb/freqcorrect_cc.h"
#include "dvb/complex_adjust_cc.h"
#include "dvb/fifo_shift_register_bb.h"
#include "dvb/complex_to_interleaved_float.h"
#include "dvb/drop.h"
#include "dvb/pad_mpeg_ts_packet_bp.h"
#include "dvb/depad_mpeg_ts_packet_pb.h"
#include "dvb/pad_dvb_packet_rs_encoded_bp.h"
#include "dvb/depad_dvb_packet_rs_encoded_pb.h"
#include "dvb/puncture_bb.h"
#include "dvb/depuncture_ff.h"
#include "dvb/randomizer_pp.h"
#include "dvb/derandomizer_pp.h"
#include "dvb/rs_encoder_pp.h"
#include "dvb/rs_decoder_pp.h"
#include "dvb/sync_decoder.h"
#include "dvb/depuncture_viterbi_cb.h"
#include "dvb/depad_mpeg_ts_packet_pb.h"
#include "dvb/pad_dvb_packet_rs_encoded_bp.h"
#include "dvb/depad_dvb_packet_rs_encoded_pb.h"
#include "dvb/puncture_bb.h"
#include "dvb/depuncture_ff.h"
#include "dvb/randomizer_pp.h"
#include "dvb/derandomizer_pp.h"
#include "dvb/rs_encoder_pp.h"
#include "dvb/rs_decoder_pp.h"
#include "dvb/sync_decoder.h"
#include "dvb/depuncture_viterbi_cb.h"
%}


%include "dvb/freqcorrect_cc.h"
GR_SWIG_BLOCK_MAGIC2(dvb, freqcorrect_cc);
%include "dvb/complex_adjust_cc.h"
GR_SWIG_BLOCK_MAGIC2(dvb, complex_adjust_cc);
%include "dvb/fifo_shift_register_bb.h"
GR_SWIG_BLOCK_MAGIC2(dvb, fifo_shift_register_bb);
%include "dvb/complex_to_interleaved_float.h"
GR_SWIG_BLOCK_MAGIC2(dvb, complex_to_interleaved_float);
%include "dvb/drop.h"
GR_SWIG_BLOCK_MAGIC2(dvb, drop);
%include "dvb/pad_mpeg_ts_packet_bp.h"
GR_SWIG_BLOCK_MAGIC2(dvb, pad_mpeg_ts_packet_bp);
%include "dvb/depad_mpeg_ts_packet_pb.h"
GR_SWIG_BLOCK_MAGIC2(dvb, depad_mpeg_ts_packet_pb);
%include "dvb/pad_dvb_packet_rs_encoded_bp.h"
GR_SWIG_BLOCK_MAGIC2(dvb, pad_dvb_packet_rs_encoded_bp);
%include "dvb/depad_dvb_packet_rs_encoded_pb.h"
GR_SWIG_BLOCK_MAGIC2(dvb, depad_dvb_packet_rs_encoded_pb);
%include "dvb/puncture_bb.h"
GR_SWIG_BLOCK_MAGIC2(dvb, puncture_bb);
%include "dvb/depuncture_ff.h"
GR_SWIG_BLOCK_MAGIC2(dvb, depuncture_ff);
%include "dvb/randomizer_pp.h"
GR_SWIG_BLOCK_MAGIC2(dvb, randomizer_pp);
%include "dvb/derandomizer_pp.h"
GR_SWIG_BLOCK_MAGIC2(dvb, derandomizer_pp);
%include "dvb/rs_encoder_pp.h"
GR_SWIG_BLOCK_MAGIC2(dvb, rs_encoder_pp);
%include "dvb/rs_decoder_pp.h"
GR_SWIG_BLOCK_MAGIC2(dvb, rs_decoder_pp);
%include "dvb/sync_decoder.h"
GR_SWIG_BLOCK_MAGIC2(dvb, sync_decoder);
%include "dvb/depuncture_viterbi_cb.h"
GR_SWIG_BLOCK_MAGIC2(dvb, depuncture_viterbi_cb);

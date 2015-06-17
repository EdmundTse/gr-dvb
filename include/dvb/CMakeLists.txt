# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Install public header files
########################################################################
install(FILES
    api.h
    freqcorrect_cc.h
    complex_adjust_cc.h
    fifo_shift_register_bb.h
    complex_to_interleaved_float.h
    drop.h
    pad_mpeg_ts_packet_bp.h
    depad_mpeg_ts_packet_pb.h
    depad_mpeg_ts_packet_pb.h
    pad_dvb_packet_rs_encoded_bp.h
    depad_dvb_packet_rs_encoded_pb.h
    puncture_bb.h
    depuncture_ff.h
    randomizer_pp.h
    derandomizer_pp.h
    rs_encoder_pp.h
    rs_decoder_pp.h
    sync_decoder.h
    depuncture_viterbi_cb.h DESTINATION include/dvb
)

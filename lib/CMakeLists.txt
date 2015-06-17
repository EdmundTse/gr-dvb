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
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND dvb_sources
    freqcorrect_cc_impl.cc
    complex_adjust_cc_impl.cc
    fifo_shift_register_bb_impl.cc
    complex_to_interleaved_float_impl.cc
    drop_impl.cc
    pad_mpeg_ts_packet_bp_impl.cc
    depad_mpeg_ts_packet_pb_impl.cc
    depad_mpeg_ts_packet_pb_impl.cc
    pad_dvb_packet_rs_encoded_bp_impl.cc
    depad_dvb_packet_rs_encoded_pb_impl.cc
    puncture_bb_impl.cc
    depuncture_ff_impl.cc
    dvb_randomizer.cc
    randomizer_pp_impl.cc
    derandomizer_pp_impl.cc
    dvb_rs.cc
    rs_encoder_pp_impl.cc
    rs_decoder_pp_impl.cc 
    dvb_sync_search.cc
    sync_decoder_impl.cc
    depuncture_viterbi_cb_impl.cc )

set(dvb_sources "${dvb_sources}" PARENT_SCOPE)
if(NOT dvb_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT dvb_sources)

add_library(gnuradio-dvb SHARED ${dvb_sources})
target_link_libraries(gnuradio-dvb ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES} gnuradio-trellis gnuradio-fec)
set_target_properties(gnuradio-dvb PROPERTIES DEFINE_SYMBOL "gnuradio_dvb_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-dvb PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-dvb
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})
list(APPEND test_dvb_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_dvb.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_dvb.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_dvb_randomizer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_dvb_sync_search.cc
)

add_executable(test-dvb ${test_dvb_sources})

target_link_libraries(
  test-dvb
  ${GNURADIO_RUNTIME_LIBRARIES}
  gnuradio-fec
  gnuradio-trellis
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-dvb
)

GR_ADD_TEST(test_dvb test-dvb)

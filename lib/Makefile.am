include $(top_srcdir)/Makefile.common

# list of programs run by "make check" and "make distcheck"
TESTS = test_all

# ----------------------------------------------------------------
# DVB C++ library: libgnuradio-dvb.so
# ----------------------------------------------------------------

# C/C++ headers get installed in ${prefix}/include/$(modname)
modinclude_HEADERS = \
	dvb_consts.h \
	dvb_types.h \
	dvb_pad.h \
	dvb_complex_to_interleaved_float.h \
	dvb_puncture.h \
	dvb_fifo_shift_register_bb.h \
	dvb_freqcorrect_cc.h \
	dvb_rs_pp.h \
	dvb_randomizer_pp.h \
	dvb_complex_adjust_cc.h \
	dvb_drop.h \
	dvb_sync_decoder.h \
	dvb_depuncture_viterbi_cb.h \
	dvb_randomizer_impl.h \
	dvb_rs_impl.h \
	dvb_sync_search_impl.h

lib_LTLIBRARIES = libgnuradio-dvb.la

libgnuradio_dvb_la_SOURCES = \
	dvb_types.cc \
	dvb_pad.cc \
	dvb_complex_to_interleaved_float.cc \
	dvb_puncture.cc \
	dvb_fifo_shift_register_bb.cc \
	dvb_freqcorrect_cc.cc \
	dvb_rs_pp.cc \
	dvb_randomizer_pp.cc \
	dvb_complex_adjust_cc.cc \
	dvb_drop.cc \
	dvb_sync_decoder.cc \
	dvb_depuncture_viterbi_cb.cc \
	dvb_randomizer_impl.cc \
	dvb_rs_impl.cc \
	dvb_sync_search_impl.cc

libgnuradio_dvb_la_LIBADD = \
	$(GNURADIO_CORE_LA)

libgnuradio_dvb_la_LDFLAGS = \
	$(NO_UNDEFINED)

# ----------------------------------------------------------------
# DVB C++ QA library: libgnuradio-dvb-qa.so (not installed)
# ----------------------------------------------------------------

noinst_LTLIBRARIES = libgnuradio-dvb-qa.la

libgnuradio_dvb_qa_la_SOURCES = \
	qa_dvb.cc \
	qa_dvb_randomizer_impl.cc \
	qa_dvb_sync_search_impl.cc \
	qa_dvb_utils.cc

libgnuradio_dvb_qa_la_LDFLAGS = $(NO_UNDEFINED) -version-info 0:0:0

libgnuradio_dvb_qa_la_LIBADD = \
	libgnuradio-dvb.la \
	$(CPPUNIT_LIBS)

# ----------------------------------------------------------------
# headers that don't get installed
# ----------------------------------------------------------------
noinst_HEADERS = \
	qa_dvb.h \
	qa_dvb_randomizer_impl.h \
	qa_dvb_sync_search_impl.h \
	qa_dvb_utils.h

# ----------------------------------------------------------------
# test program
# ----------------------------------------------------------------
noinst_PROGRAMS = \
	test_all

test_all_SOURCES = test_all.cc
test_all_LDADD   = libgnuradio-dvb-qa.la

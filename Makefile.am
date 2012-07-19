ACLOCAL_AMFLAGS = -I config

include $(top_srcdir)/Makefile.common

EXTRA_DIST = \
	bootstrap \
	configure \
	config.h.in \
	Makefile.swig \
	Makefile.swig.gen.t \
	version.sh \
	README \
	README.hacking

SUBDIRS = config lib swig python grc

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA =

DISTCLEANFILES = gr-dvb*.tar.gz

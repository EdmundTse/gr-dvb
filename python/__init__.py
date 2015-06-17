# Copyright (c) 2010 Edmund Tse
#               2015 Santiago Piccinini
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

'''
This is the GNU Radio DVB module. Place your Python package
description here (python/__init__.py).
'''

# import swig generated symbols into the dvb namespace
try:
	# this might fail if the module is python-only
	from dvb_swig import *
except ImportError:
	pass

# MPEG Transport Stream constants
MPEG_TS_SYNC_BYTE	= 0x47
MPEG_TS_PKT_LENGTH				= 188
MPEG_TS_ERROR_BIT	= 0x80	# top bit of byte after SYNC

# Reed-Solomon parameters
DVB_RS_ENCODED_LENGTH	= 204	# i.e. RS(204,188)
DVB_RS_PAD_LENGTH		= 51	# Shortened from RS(255,239) code by padding with 51 zeros
DVB_RS_SYMSIZE			= 8	# Bits per symbol
DVB_RS_GFPOLY			= 0x11d# Extended Galois field generator polynomial coefficients, with the 0th coefficient in the low order bit. The polynomial must be primitive.
DVB_RS_FCR				= 0	# First consecutive root of the generator polynomial in index form
DVB_RS_PRIM			= 0x01	# Primitive element to generate polynomial roots
DVB_RS_NROOTS			= 16	# Number of generator roots = number of parity symbols

# Interleaver parameters
DVB_INTERLEAVER_I		= 12	# Interleaving depth
DVB_INTERLEAVER_M		= 17	# Cell size

# Randomiser constants
MPEG_TS_SYNC_BYTE_INV = MPEG_TS_SYNC_BYTE ^ 0xFF
DVB_RANDOMIZER_INVERTED_SYNC_PERIOD = 8
DVB_RANDOMIZER_PERIOD	= MPEG_TS_PKT_LENGTH * DVB_RANDOMIZER_INVERTED_SYNC_PERIOD

k = 1
n = 2
G_array = [0171, 0133]
K = 204 * 8
dimensionality = 2
#c_array[] = {0.7, 0.7, 0.7, -0.7, -0.7, 0.7, -0.7, -0.7};

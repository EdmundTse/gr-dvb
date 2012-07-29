# Copyright (c) 2010 Edmund Tse
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

#!/usr/bin/env python

from gnuradio import gr, trellis
import dvb_swig

# This is equal to dvb.G_array; works around C++ type mapping
G = (0171, 0133)

class convolutional_encoder_bb(gr.hier_block2):
	"""
	DVB Convolutional Encoder

	Input: unsigned char (unpacked bits)
	Output: unsigned char (symbols)
	"""
	def __init__(self):
		gr.hier_block2.__init__(self, "dvb_convolutional_encoder_bb",
				gr.io_signature(1, 1, gr.sizeof_char),	# Input signature
				gr.io_signature(1, 1, gr.sizeof_char))	# Output signature

		self.encoder = trellis.encoder_bb(trellis.fsm(dvb_swig.k, dvb_swig.n, G), dvb_swig.dimensionality)
		self.unpack = gr.unpack_k_bits_bb(dvb_swig.dimensionality)

		self.connect(self, self.encoder, self.unpack, self)

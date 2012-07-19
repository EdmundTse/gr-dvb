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

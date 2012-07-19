#!/usr/bin/env python

from gnuradio import gr
import dvb_swig

INTERLEAVER_M = 17		# Length of each shift register cell (DVB standard)
INTERLEAVER_I = 12		# Interleaving depth (DVB standard)
DELAY = 2 * sum(range(INTERLEAVER_I)) * INTERLEAVER_M

class interleaver_bb(gr.hier_block2):
	"""
	Forney convolutional interleaver
	"""
	def __init__(self):
		gr.hier_block2.__init__(self, "interleaver",
				gr.io_signature(1, 1, gr.sizeof_char),	# Input signature
				gr.io_signature(1, 1, gr.sizeof_char))	# Output signature

		self.demux = gr.stream_to_streams(gr.sizeof_char, INTERLEAVER_I)
		self.shift_registers = [dvb_swig.fifo_shift_register_bb(INTERLEAVER_M * j)
				for j in range(INTERLEAVER_I)]
		self.mux = gr.streams_to_stream(gr.sizeof_char, INTERLEAVER_I)

		self.connect(self, self.demux)
		for j in range(INTERLEAVER_I):
			self.connect((self.demux, j), self.shift_registers[j], (self.mux, j))
		self.connect(self.mux, self)

class deinterleaver_bb(gr.hier_block2):
	"""
	Forney convolutional deinterleaver
	"""
	def __init__(self):
		gr.hier_block2.__init__(self, "deinterleaver",
				gr.io_signature(1, 1, gr.sizeof_char),	# Input signature
				gr.io_signature(1, 1, gr.sizeof_char))	# Output signature

		self.demux = gr.stream_to_streams(gr.sizeof_char, INTERLEAVER_I)
		self.shift_registers = [dvb_swig.fifo_shift_register_bb(INTERLEAVER_M * j)
				for j in range(INTERLEAVER_I)]
		# Deinterleaver shift registers are reversed compared to interleaver
		self.shift_registers.reverse()
		self.mux = gr.streams_to_stream(gr.sizeof_char, INTERLEAVER_I)
		# Remove the uninitialised zeros that come out of the deinterleaver
		self.skip = gr.skiphead(gr.sizeof_char, DELAY)

		self.connect(self, self.demux)
		for j in range(INTERLEAVER_I):
			self.connect((self.demux, j), self.shift_registers[j], (self.mux, j))
		self.connect(self.mux, self.skip, self)

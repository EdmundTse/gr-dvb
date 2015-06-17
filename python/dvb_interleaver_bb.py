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

from gnuradio import gr, blocks
import dvb

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

		self.demux = blocks.stream_to_streams(gr.sizeof_char, INTERLEAVER_I)
		self.shift_registers = [dvb.fifo_shift_register_bb(INTERLEAVER_M * j)
				for j in range(INTERLEAVER_I)]
		self.mux = blocks.streams_to_stream(gr.sizeof_char, INTERLEAVER_I)

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

		self.demux = blocks.stream_to_streams(gr.sizeof_char, INTERLEAVER_I)
		self.shift_registers = [dvb.fifo_shift_register_bb(INTERLEAVER_M * j)
				for j in range(INTERLEAVER_I)]
		# Deinterleaver shift registers are reversed compared to interleaver
		self.shift_registers.reverse()
		self.mux = blocks.streams_to_stream(gr.sizeof_char, INTERLEAVER_I)
		# Remove the uninitialised zeros that come out of the deinterleaver
		self.skip = blocks.skiphead(gr.sizeof_char, DELAY)

		self.connect(self, self.demux)
		for j in range(INTERLEAVER_I):
			self.connect((self.demux, j), self.shift_registers[j], (self.mux, j))
		self.connect(self.mux, self.skip, self)

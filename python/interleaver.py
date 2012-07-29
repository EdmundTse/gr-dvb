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
"""
A pure python implementation of the DVB interleaver for verification purposes
"""

class shift_register(object):
	def __init__(self, length):
		self.length = length
		self.data = [0] * length
		self.index = 0

	def shift(self, in_data):
		if self.length == 0:
			return in_data
		ret = self.data[self.index]
		self.data[self.index] = in_data
		self.index = (self.index + 1) % self.length
		return ret

class interleaver(object):
	I = 12	# Interleaving depth
	M = 17	# Cell size

	def __init__(self):
		self.index = 0
		self.shift_registers = [shift_register(i * interleaver.M) for i in range(interleaver.I)]

	def next(self, in_data):
		ret = self.shift_registers[self.index].shift(in_data)
		self.index = (self.index + 1) % len(self.shift_registers)
		return ret

class deinterleaver(object):
	I = 12	# Interleaving depth
	M = 17	# Cell size

	def __init__(self):
		self.index = 0
		self.shift_registers = [shift_register(i * interleaver.M) for i in range(interleaver.I - 1, -1, -1)]

	def next(self, in_data):
		ret = self.shift_registers[self.index].shift(in_data)
		self.index = (self.index + 1) % interleaver.I
		return ret

if __name__ == '__main__':
	in_data = range(1, 2500)
	delay = 2 * sum(range(interleaver.I)) * interleaver.M

	inter = interleaver()
	interleaved = [inter.next(i) for i in in_data]
	deint = deinterleaver()
	deinterleaved = [deint.next(i) for i in interleaved]
	print in_data[:-delay]
	print deinterleaved[delay:]

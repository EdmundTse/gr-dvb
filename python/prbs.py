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
import sys
import binascii

class lfsr:
	"""
	A linear feedback shift register with parallel data reset.
	"""
	def __init__(self, poly, length, initial_value = 0):
		"""
		Constructor for the LFSR
		poly: e.g. 1 + x + x3 + x4 in a len 4 lfsr would be: 1011b
		length: number of buffers in the shift register
		initial_value: initial contents of the 
		"""
		self.poly = poly | 1
		self.length = length
		# Truncate initial value to just the bits within the LFSR length
		self.data = (1 << length) - 1
		self.data = self.data & initial_value

	def get_value(self):
		return self.data

	def reset(self, value):
		self.data = value

	def next_state(self):
		bits = self.data & self.poly

		output = 0
		# XOR the tapped bits together
		while bits != 0:
			lsb = bits & 1
			output = output ^ lsb
			bits = bits >> 1

		self.data = self.data >> 1
		self.data = self.data | output << self.length - 1

		return output

def randomizer_prbs():
	"""
	Returns 1503 bytes PRBS as required in the DVB-S randomizer.
	"""
	# Create a polynomial of "1 + x^14 + x^15"
	poly =			int('000000000000011', 2)
	initial_value =	int('100101010000000', 2)
	reg = lfsr(poly, 15, initial_value)
	prbs = []
	for i in range(1503):
		byte = 0
		# Generate and pack next byte
		for i in range(8):
			byte = byte << 1
			byte = byte | reg.next_state()
		prbs.append(byte)
	return prbs

def randomizer_xor_sequence():
	"""
	Returns the 1504 bytes to be XORed with every 8 MPEG2-TS packets.
	"""
	seq = randomizer_prbs()

	# The first sync byte is to be inverted, i.e. XORed 0xFF
	seq.insert(0, 0xFF)

	# Afterwards, every sync byte is ignored, so need them to be 0
	for i in range(1,8):
		seq[188*i] = 0x00
	
	return seq

if __name__ == "__main__":
	"""
	This script generates the sequence needed to XOR by the randomizer, and
	outputs them in C format.
	"""
	seq = randomizer_xor_sequence()
	
	sys.stdout.write("const char sequence[] = {")
	for i in range(len(seq)):
		if i % 8 == 0:
			print
			sys.stdout.write("\t")
		else:
			sys.stdout.write(" ")

		sys.stdout.write("0x%02X" % seq[i])
		if i != len(seq) - 1:
			sys.stdout.write(",")
		else:
			print
	print "};"

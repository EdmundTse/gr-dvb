#
# Copyright 2010 Free Software Foundation, Inc.
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
#

# This file is mostly copied from GNU Radio ATSC code

from gnuradio import gr
import random
import dvb

random_byte = lambda: random.randint(0, 255)

class memoize(object):
	def __init__(self, thunk):
		self.thunk = thunk
		self.cached = False
		self.value = None

	def __call__(self):
		if self.cached:
			return self.value
		self.value = self.thunk()
		self.cached = True
		return self.value

# Make a fake transport stream that's big enough for our purposes.
make_transport_stream = memoize(lambda : tuple(make_fake_transport_stream_packet(8 * 100)))

def make_fake_transport_stream_packet(npkts):
    """
    Return a sequence of 8-bit ints that represents an MPEG Transport Stream packet.

    @param npkts: how many 188-byte packets to return

    FYI, each ATSC Data Frame contains two Data Fields, each of which contains
    312 data segments.  Each transport stream packet maps to a data segment.
    """
    r = [0] * (npkts * 188)
    i = 0
    for j in range(npkts):
        r[i+0] = dvb.MPEG_TS_SYNC_BYTE
        r[i+1] = random.randint(0, 127) # top bit (transport error bit) clear
        i = i + 2
        for n in range(186):
            r[i + n] = random.randint(0, 255)
        i = i + 186

    return r

def check_sync_bytes(testcase, data, randomized=False, packet_length=dvb.MPEG_TS_PKT_LENGTH):
	"""
	Checks the presence of SYNC bytes at the start of each packet
	"""
	inverted_sync_byte_period = packet_length * dvb.DVB_RANDOMIZER_INVERTED_SYNC_PERIOD
	for i in xrange(0, len(data), packet_length):
		try:
			if randomized and i % (inverted_sync_byte_period) == 0:
				testcase.assertEqual(dvb.MPEG_TS_SYNC_BYTE ^ 0xFF, data[i])
			else:
				testcase.assertEqual(dvb.MPEG_TS_SYNC_BYTE, data[i])
		except AssertionError as err:
			print "Assertion failed at i = %d: %s" % (i, err)
			raise err


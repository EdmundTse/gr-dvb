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

from gnuradio import gr, gr_unittest, trellis, digital
import dvb_swig
import dvb_interleaver_bb
import dvb_convolutional_encoder_bb
import dvb_s_modulator

import random, copy, math
from dvb_utils import *

class qa_dvb(gr_unittest.TestCase):
	"""
	Unit tests for the DVB package
	"""
	def setUp(self):
		self.tb = gr.top_block()

	def tearDown(self):
		self.tb = None

	def test_complex_to_interleaved_float(self):
		"""
		Tests the conversion from complex to interleaved floats
		"""
		src_data = [complex(x/10.0) for x in range(100)]
		expected_result = tuple([x/20.0 if x % 2 == 0 else 0 for x in range(200)])

		src = gr.vector_source_c(src_data)
		c2f = dvb_swig.complex_to_interleaved_float()
		dst = gr.vector_sink_f()
		
		self.tb.connect(src, c2f, dst)
		self.tb.run()
		for x in zip(expected_result, dst.data()):
			self.assertAlmostEqual(x[0], x[1], 4)

	def test_loopback_pad_depad_mpeg_ts_packet(self):
		"""
		Loopback test: source data padding and depadding
		"""
		src_data = make_transport_stream()
		expected_result = src_data
		check_sync_bytes(self, src_data)

		src = gr.vector_source_b(src_data)
		pad = dvb_swig.pad_mpeg_ts_packet_bp()
		depad = dvb_swig.depad_mpeg_ts_packet_pb()
		dst = gr.vector_sink_b()

		self.tb.connect(src, pad, depad, dst)
		self.tb.run()
		self.assertEqual(expected_result, dst.data())

	def test_loopback_pad_depad_dvb_packet_rs_encoded(self):
		"""
		Loopback test: source data padding and depadding
		"""
		# Source data must have length of a multiple of 204 bytes, otherwise
		# the block will ignore the final incomplete packet
		src_data = tuple([random_byte() for i in range(204 * 20)])
		expected_result = src_data

		src = gr.vector_source_b(src_data)
		pad = dvb_swig.pad_dvb_packet_rs_encoded_bp()
		depad = dvb_swig.depad_dvb_packet_rs_encoded_pb()
		dst = gr.vector_sink_b()

		self.tb.connect(src, pad, depad, dst)
		self.tb.run()
		self.assertEqual(expected_result, dst.data())

	def randomizer_derandomizer_with_length(self, npackets):
		"""
		Loopback randomiser to derandomiser
		Note: This method itself is not a unit test method.
		"""
		src_data = make_fake_transport_stream_packet(npackets)
		check_sync_bytes(self, src_data)
		expected_result = tuple(src_data)

		src = gr.vector_source_b(src_data)
		pad = dvb_swig.pad_mpeg_ts_packet_bp()
		randomizer = dvb_swig.randomizer_pp()
		derandomizer = dvb_swig.derandomizer_pp()
		depad = dvb_swig.depad_mpeg_ts_packet_pb()
		dst = gr.vector_sink_b()

		# Connect and run
		self.tb.connect(src, pad, randomizer, derandomizer, depad, dst)
		self.tb.run()
		# Check that the decoded bytes are the same as original
		self.assertEqual(expected_result, dst.data())

	def test_randomizer_pp_short_sequence(self):
		# Test block behaviour whem zero length input is given
		self.randomizer_derandomizer_with_length(0);
		self.randomizer_derandomizer_with_length(1);

		# The 8th packet is the last packet before we expect the LFSR to reset
		self.randomizer_derandomizer_with_length(7);
		self.randomizer_derandomizer_with_length(8);
		self.randomizer_derandomizer_with_length(9);

	def test_randomizer_pp_sync_bytes(self):
		"""
		Tests correctness of sync bytes
		"""
		src_data = make_transport_stream()
		check_sync_bytes(self, src_data)

		src = gr.vector_source_b(src_data)
		pad = dvb_swig.pad_mpeg_ts_packet_bp()
		randomizer = dvb_swig.randomizer_pp()
		depad = dvb_swig.depad_mpeg_ts_packet_pb()
		dst = gr.vector_sink_b()

		# Connect and run
		self.tb.connect(src, pad, randomizer, depad, dst)
		self.tb.run()
		# Check sync bytes
		result_data = dst.data()
		self.assertEqual(len(src_data), len(result_data))
		check_sync_bytes(self, result_data, randomized=True)

	def derandomizer_pp_desync(self, offset):
		"""
		Tests the ability of the derandomiser to synchronise when the inverted SYNC is <offset> packets away
		Note: This method itself is not a unit test method.
		"""
		assert offset < 8

		useful_data = make_transport_stream()
		src = gr.vector_source_b(useful_data)
		pad = dvb_swig.pad_mpeg_ts_packet_bp()
		randomizer = dvb_swig.randomizer_pp()
		depad = dvb_swig.depad_mpeg_ts_packet_pb()
		dst = gr.vector_sink_b()
		self.tb.connect(src, pad, randomizer, depad, dst)
		self.tb.run()
		randomized_data = dst.data()

		src_data = make_fake_transport_stream_packet(offset)
		src_data.extend(randomized_data)

		self.tb = gr.top_block()
		src = gr.vector_source_b(src_data)
		pad = dvb_swig.pad_mpeg_ts_packet_bp()
		derandomizer = dvb_swig.derandomizer_pp()
		depad = dvb_swig.depad_mpeg_ts_packet_pb()
		dst = gr.vector_sink_b()

		self.tb.connect(src, pad, derandomizer, depad, dst)
		self.tb.run()
		result_data = dst.data()
		self.assertEqual(tuple(useful_data), result_data[-len(useful_data):])
	
	def test_derandomizer_pp_desync(self):
		# When the input is perfectly synchronised
		self.derandomizer_pp_desync(0)

		# When the start of the sequence of 8 packets has some number of offset
		self.derandomizer_pp_desync(1)
		self.derandomizer_pp_desync(7)

	def rs_coder_pp_with_error(self, num_errors):
		"""
		Tests the RS encoder and decoder with given number of error bytes
		Note: This method itself is not a unit test method.
		"""
		src_data = tuple(make_fake_transport_stream_packet(1))

		# Encode
		src = gr.vector_source_b(src_data)
		pad = dvb_swig.pad_mpeg_ts_packet_bp()
		rs_encoder = dvb_swig.rs_encoder_pp()
		depad = dvb_swig.depad_dvb_packet_rs_encoded_pb()
		dst = gr.vector_sink_b()

		self.tb.connect(src, pad, rs_encoder, depad, dst)
		self.tb.run()

		# Introduce errors
		encoded = list(dst.data())
		errors = set()
		while len(errors) < num_errors:
			errors.add(random.randint(0, len(encoded)-1))
		for loc in errors:
			encoded[loc] = random_byte()

		# Decode
		self.tb = gr.top_block()
		src = gr.vector_source_b(encoded)
		pad = dvb_swig.pad_dvb_packet_rs_encoded_bp()
		rs_decoder = dvb_swig.rs_decoder_pp()
		depad = dvb_swig.depad_mpeg_ts_packet_pb()
		dst = gr.vector_sink_b()

		self.tb.connect(src, pad, rs_decoder, depad, dst)
		self.tb.run()
		# Check that the decoded bytes are the same as original
		self.assertEqual(src_data, dst.data())

	def test_rs_coder_pp_error_correction(self):
		self.rs_coder_pp_with_error(0)		# Perfect channel with no errors
		self.rs_coder_pp_with_error(8)		# Maximum errors = 16/2 = 8

	def shift_register_bb_length(self, sr_length):
		"""
		FIFO Shift Register
		Note: This method itself is not a unit test method
		"""
		data_length = 100
		src_data = range(data_length)
		expected_result = tuple([i - sr_length if i >= sr_length else 0 for i in range(data_length)])

		src = gr.vector_source_b(src_data)
		sr = dvb_swig.fifo_shift_register_bb(sr_length)
		dst = gr.vector_sink_b()

		# Connect and run
		self.tb.connect(src, sr, dst)
		self.tb.run()

		# Check results against expected data
		result_data = dst.data()
		self.assertEqual(expected_result[sr_length:], result_data[sr_length:])

	def test_shift_register_bb(self):
		"""
		FIFO shift register
		"""
		# 0 length SR: Output should be exactly the input
		self.shift_register_bb_length(0)
		# Unit length SR: Output should have exactly one delay
		self.shift_register_bb_length(1)
		# General case SR
		self.shift_register_bb_length(10)
		self.shift_register_bb_length(1000)

	def test_loopback_rand_rs(self):
		"""
		Loopback src > randomiser > rs encoder > rs decoder > derandomiser > dst
		"""
		src_data = make_transport_stream()

		src = gr.vector_source_b(src_data)
		pad = dvb_swig.pad_mpeg_ts_packet_bp()
		randomizer = dvb_swig.randomizer_pp()
		rs_encoder = dvb_swig.rs_encoder_pp()
		rs_decoder = dvb_swig.rs_decoder_pp()
		derandomizer = dvb_swig.derandomizer_pp()
		depad = dvb_swig.depad_mpeg_ts_packet_pb()
		dst = gr.vector_sink_b()

		# Connect and run
		self.tb.connect(src, pad, randomizer, rs_encoder, rs_decoder, derandomizer, depad, dst)
		self.tb.run()
		# Check that the decoded bytes are the same as original
		self.assertEqual(src_data, dst.data())

	def test_interleaver_bb(self):
		"""
		DVB convolutional interleaver, deinterleaver and their associated delays
		"""
		data_length = 3000
		src_data = [i % 256 for i in range(data_length)]
		# Ensure that we check for longer than fixed delay of 2244 bytes total to be meaningful
		self.assertTrue(data_length > dvb_interleaver_bb.DELAY)
		# We expect only the bytes prior to DELAY - they're still in the shift registers
		expected_result = tuple(src_data[:-dvb_interleaver_bb.DELAY])

		src = gr.vector_source_b(src_data)
		interleaver = dvb_interleaver_bb.interleaver_bb()
		deinterleaver = dvb_interleaver_bb.deinterleaver_bb()
		dst = gr.vector_sink_b()

		self.tb.connect(src, interleaver, deinterleaver, dst)
		self.tb.run()
		self.assertEqual(expected_result, dst.data())

	def test_loopback_rand_rs_int(self):
		"""
		Loopback of data, (de)randomiser, rs (en/de)coder, (de)interleaver
		"""
		src_data = make_transport_stream()
		# Disregard end bytes of source data, accounting for interleaver delay
		expected_delay = dvb_interleaver_bb.DELAY * \
				dvb_swig.MPEG_TS_PKT_LENGTH / dvb_swig.DVB_RS_ENCODED_LENGTH
		expected_result = tuple(src_data[:-expected_delay])

		src = gr.vector_source_b(src_data)
		txpad = dvb_swig.pad_mpeg_ts_packet_bp()
		randomizer = dvb_swig.randomizer_pp()
		rs_encoder = dvb_swig.rs_encoder_pp()
		txdepad = dvb_swig.depad_dvb_packet_rs_encoded_pb()
		interleaver = dvb_interleaver_bb.interleaver_bb()
		deinterleaver = dvb_interleaver_bb.deinterleaver_bb()
		rxpad = dvb_swig.pad_dvb_packet_rs_encoded_bp()
		rs_decoder = dvb_swig.rs_decoder_pp()
		derandomizer = dvb_swig.derandomizer_pp()
		rxdepad = dvb_swig.depad_mpeg_ts_packet_pb()
		dst = gr.vector_sink_b()

		# Connect and run
		self.tb.connect(src, txpad, randomizer, rs_encoder, txdepad, interleaver, deinterleaver)
		self.tb.connect(deinterleaver, rxpad, rs_decoder, derandomizer, rxdepad, dst)
		self.tb.run()
		# Check that the decoded bytes are the same as original
		self.assertEqual(expected_result, dst.data())

	def puncture_bb(self, P, seq_len=100):
		"""
		Tests that the puncture block correctly drops bytes from a sequence
		Note: This method itself is not a unit test method.
		"""
		src_data = [random.randint(0,1) for _ in range(seq_len)]
		expected_result = tuple([i[0] for i in zip(src_data, range(len(src_data))) if P[i[1] % len(P)] != 0])

		src = gr.vector_source_b(src_data)
		puncture = dvb_swig.puncture_bb(P)
		dst = gr.vector_sink_b()

		self.tb.connect(src, puncture, dst)
		self.tb.run()
		self.assertEqual(expected_result, dst.data())

	def test_puncture_bb(self):
		# Empty sequence disabled 21 Sep 10 due to {ticket:1}
		# self.puncture_bb([])			# Empty puncture sequence
		self.puncture_bb([1,1])			# No puncturing
		self.puncture_bb([1,1,0,1])		# Puncturing for 2/3 rate
		self.puncture_bb([1,1,0,1,1,0])	# Puncturing for 3/4 rate
		self.puncture_bb([1,1,0,1,1,0,0,1,1,0])		# for 5/6 rate
		self.puncture_bb([1,1,0,1,0,1,0,1,1,0,0,1,1,0])	# 7/8 rate

	def depuncture_puncture(self, P, seq_len=100):
		"""
		Tests that the depuncture block is matched to the puncture block
		Note: This method itself is not a unit test method.
		"""
		src_data = [random.randint(0,1) for _ in range(seq_len)]
		expected_result = tuple(src_data)

		src = gr.vector_source_f(src_data)
		depuncture = dvb_swig.depuncture_ff(P)
		f2c = gr.float_to_uchar()
		puncture = dvb_swig.puncture_bb(P)
		dst = gr.vector_sink_b()

		self.tb.connect(src, depuncture, f2c, puncture, dst)
		self.tb.run()
		self.assertEqual(expected_result, dst.data())

	def test_depuncture_puncture(self):
		self.depuncture_puncture([1,1])			# No puncturing
		self.depuncture_puncture([1,1,0,1])		# Puncturing for 2/3 rate
		self.depuncture_puncture([1,1,0,1,1,0])	# Puncturing for 3/4 rate
		self.depuncture_puncture([1,1,0,1,1,0,0,1,1,0])		# for 5/6 rate
		self.depuncture_puncture([1,1,0,1,0,1,0,1,1,0,0,1,1,0])	# 7/8 rate

	def test_depuncture_viterbi_cb(self):
		"""
		Performs some very basic tests of the depuncture-viterbi block
		"""
		# 1. Random data
		expected_result = ()

		src = gr.noise_source_c(gr.GR_GAUSSIAN, ampl=math.sqrt(1/2), seed=0)
		head = gr.head(gr.sizeof_gr_complex, 100000)
		depuncture_viterbi = dvb_swig.depuncture_viterbi_cb([1,1])
		dst = gr.vector_sink_b()

		self.tb.connect(src, head, depuncture_viterbi, dst)
		self.tb.run()
		self.assertEqual(expected_result, dst.data());

	def test_convolutional_encoder(self):
		"""
		Tests convolutional encoder
		"""
		src_data = make_transport_stream()
		constellation = [.7, .7,.7,-.7,-.7,.7,-.7,-.7]

		src = gr.vector_source_b(src_data)
		unpack = gr.packed_to_unpacked_bb(1, gr.GR_MSB_FIRST)
		enc = dvb_convolutional_encoder_bb.convolutional_encoder_bb()
		repack1 = gr.unpacked_to_packed_bb(1, gr.GR_MSB_FIRST)
		repack2 = gr.packed_to_unpacked_bb(2, gr.GR_MSB_FIRST)
		mapper = gr.chunks_to_symbols_bf(constellation, dvb_swig.dimensionality)
		viterbi = trellis.viterbi_combined_fb(trellis.fsm(dvb_swig.k, dvb_swig.n, dvb_convolutional_encoder_bb.G),
				dvb_swig.K, -1, -1, dvb_swig.dimensionality, constellation, digital.TRELLIS_EUCLIDEAN)
		pack = gr.unpacked_to_packed_bb(1, gr.GR_MSB_FIRST)
		dst = gr.vector_sink_b()

		self.tb.connect(src, unpack, enc, repack1, repack2, mapper)
		self.tb.connect(mapper, viterbi, pack, dst)
		self.tb.run()
		result_data = dst.data()
		self.assertEqual(tuple(src_data[:len(result_data)]), result_data)

if __name__ == '__main__':
	gr_unittest.main ()

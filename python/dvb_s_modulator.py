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

from gnuradio import gr, digital
from math import pi
import dvb_swig

M = 4						# QPSK is of order 4
nfilts = 32

mod_constellation = digital.constellation_qpsk()

# Receiver parameters
(fmin, fmax) = (-0.5, 0.5)	# Allow Costas frequency swing of +/- half of the sample rate
freq_alpha = 0.01			# FLL alpha gain
freq_bw = 0.035				# Will be overriden by set_alpha(), set_beta()
timing_alpha = 0.10			# Costas loop gain for frequency adjustments
timing_beta = 0.01			# Costas loop gain for phase adjustments
phase_alpha = 0.01
phase_bw = 0.035			# Will be overriden by set_alpha(), set_beta()

class s_modulator_bc(gr.hier_block2):
	"""
	DVB-S modulator

	Input: unsigned char (unpacked bits)
	Output: gr_complex (complex baseband samples)
	"""
	def __init__(self, sample_rate, symbol_rate):
		gr.hier_block2.__init__(self, "dvb_s_modulator_bc",
				gr.io_signature(1, 1, gr.sizeof_char),			# Input signature
				gr.io_signature(1, 1, gr.sizeof_gr_complex))	# Output signature

		samples_per_symbol = sample_rate / symbol_rate
		if samples_per_symbol < 2:
			raise TypeError, "Samples per symbol must be >= 2"

		# Form symbols with 2 bits per symbol
		self.pack = gr.unpacked_to_packed_bb(1, gr.GR_MSB_FIRST)
		self.reunpack = gr.packed_to_unpacked_bb(2, gr.GR_MSB_FIRST)

		self.mapper = gr.chunks_to_symbols_bc(mod_constellation)

		# Design FIR filter taps for square root raised cosine filter
		ntaps = 11 * int(samples_per_symbol * nfilts)
		rrc_taps = gr.firdes.root_raised_cosine(nfilts, nfilts, 1.0, dvb_swig.RRC_ROLLOFF_FACTOR, ntaps)
		# Baseband pulse shaping filter
		self.rrc_filter = gr.pfb_arb_resampler_ccf(samples_per_symbol, rrc_taps)

		self.connect(self, self.pack, self.reunpack, self.mapper, self.rrc_filter, self)

class s_demodulator_cc(gr.hier_block2):
	"""
	QPSK Demodulator for DVB-S
	"""
	def __init__(self, sample_rate, symbol_rate):
		gr.hier_block2.__init__(self, "dvb_s_demodulator_cc",
				gr.io_signature(1, 1, gr.sizeof_gr_complex),	# Input signature
				gr.io_signature(1, 1, gr.sizeof_gr_complex))	# Output signature

		omega = sample_rate / symbol_rate
		gain_omega = omega * omega / 4.0
		freq_beta = freq_alpha * freq_alpha / 4.0
		mu = 0.0
		gain_mu = 0.05
		omega_relative_limit = 0.005

		# Automatic gain control
		self.agc = gr.agc2_cc(
				0.06,				# Attack rate
				0.001,				# Decay rate
				1,					# Reference
				1,					# Initial gain
				100)				# Max gain

		# Frequency correction with band-edge filters FLL
		freq_beta = freq_alpha * freq_alpha / 4
		self.freq_recov = digital.fll_band_edge_cc(omega, dvb_swig.RRC_ROLLOFF_FACTOR, 11 * int(omega), freq_bw)
		self.freq_recov.set_alpha(freq_alpha)
		self.freq_recov.set_beta(freq_beta)
		self.receiver = digital.mpsk_receiver_cc(M, 0, freq_bw, fmin, fmax, mu, gain_mu, omega, gain_omega, omega_relative_limit)
		self.receiver.set_alpha(freq_alpha)
		self.receiver.set_beta(freq_beta)
		self.rotate = gr.multiply_const_cc(0.707 + 0.707j)

		self.connect(self, self.agc, self.freq_recov, self.receiver, self.rotate, self)

class s_demodulator2_cc(gr.hier_block2):
	"""
	QPSK Demodulator for DVB-S
	"""
	def __init__(self, sample_rate, symbol_rate):
		gr.hier_block2.__init__(self, "dvb_s_demodulator2_cc",
				gr.io_signature(1, 1, gr.sizeof_gr_complex),	# Input signature
				gr.io_signature(1, 1, gr.sizeof_gr_complex))	# Output signature

		samples_per_symbol = sample_rate / symbol_rate

		# Automatic gain control
		self.agc = gr.agc2_cc(
				0.06,				# Attack rate
				0.001,				# Decay rate
				1,					# Reference
				1,					# Initial gain
				100)				# Max gain

		# Frequency correction with band-edge filters FLL
		freq_beta = freq_alpha * freq_alpha / 4
		self.freq_recov = digital.fll_band_edge_cc(
				samples_per_symbol,
				dvb_swig.RRC_ROLLOFF_FACTOR,
				11 * int(samples_per_symbol),	# Size of the filter in taps
				freq_bw)
		self.freq_recov.set_alpha(freq_alpha)
		self.freq_recov.set_beta(freq_beta)


		# Symbol timing recovery with RRC data filter
		ntaps = 11 * int(samples_per_symbol * nfilts)
		rrc_taps = gr.firdes.root_raised_cosine(nfilts, nfilts,
				1.0 / samples_per_symbol, dvb_swig.RRC_ROLLOFF_FACTOR, ntaps)
		self.time_recov = gr.pfb_clock_sync_ccf(
				samples_per_symbol,				# Samples per second in the incoming signal
				timing_alpha,					# Alpha gain of control loop
				rrc_taps,						# The filter taps
				nfilts,							# Number of filters in the filter bank
				nfilts / 2)						# Initial phase to look at (or which filter to start with)
		self.time_recov.set_beta(timing_beta)

		# Perform phase / fine frequency correction using Costas PLL
		phase_beta  = phase_alpha * phase_alpha / 4
		self.phase_recov = digital.costas_loop_cc(phase_bw, M)
		self.phase_recov.set_alpha(phase_alpha)
		self.phase_recov.set_beta(phase_beta)

		self.connect(self, self.agc, self.freq_recov, self.time_recov, self.phase_recov, self)

/*
 * Copyright (c) 2010 Edmund Tse
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "dvb_depuncture_viterbi_cb.h"

static const std::vector<int> G(G_array, G_array + sizeof(G_array) / sizeof(int));
static const fsm f(k, n, G);
static const std::vector<float> constellation(c_array, c_array + sizeof(c_array) / sizeof(float));

dvb_depuncture_viterbi_cb_sptr dvb_make_depuncture_viterbi_cb(gr_vector_int sequence)
{
	return gnuradio::get_initial_sptr(new dvb_depuncture_viterbi_cb(sequence));
}

dvb_depuncture_viterbi_cb::dvb_depuncture_viterbi_cb(gr_vector_int sequence)
	: gr_hier_block2("dvb_depuncture_viterbi_cb",
			gr_make_io_signature(1, 1, sizeof(gr_complex)),
			gr_make_io_signature(1, 1, sizeof(unsigned char))),
	dropped(0),
	complex_adjust(dvb_make_complex_adjust_cc()),	// Adjusts complex signal stream
	drop(dvb_make_drop(sizeof(gr_complex))),		// Drops complex symbols for depuncture sync
	c2f(dvb_make_complex_to_interleaved_float()),
	depuncture(dvb_make_depuncture_ff(sequence)),	// 3/4 rate
	metrics(trellis_make_metrics_f(f.O(), dimensionality, constellation, TRELLIS_EUCLIDEAN)),
	viterbi(trellis_make_viterbi_b(f, K, -1, -1)),	// -1 for initial/final states not set
	sync_decoder(dvb_make_sync_decoder())
{
	assert(sequence.size() % 2 == 0);	// Expect an even number of items in the sequence (I/Q)
	assert(*std::max_element(sequence.begin(), sequence.end()) == 1);	// Puncturing matrix only has {0,1}

	unsigned int ones = std::count(sequence.begin(), sequence.end(), 1);
	alignment_boundaries = ones % 2 == 0 ? ones/2 : ones;

	// Set the sync decoder status callback function
	sync_decoder->set_status_callback(boost::bind(&dvb_depuncture_viterbi_cb::sync_decoder_callback, this, _1));

	connect(self(), 0, complex_adjust, 0);
	connect(complex_adjust, 0, drop, 0);
	connect(drop, 0, c2f, 0);
	connect(c2f, 0, depuncture, 0);
	connect(depuncture, 0, metrics, 0);
	connect(metrics, 0, viterbi, 0);
	connect(viterbi, 0, sync_decoder, 0);
	connect(sync_decoder, 0, self(), 0);
}

void dvb_depuncture_viterbi_cb::sync_decoder_callback(bool is_locked)
{
	// This function is called by the sync decoder to let us know if the
	// parameters we are using to decode the stream is correct.
	if (!is_locked)
	{
		// Switch to the next combination of parameters
		next_alignment() && next_conj() && next_phase();
/* Commented 19 Oct 10 - debugging purposes only
		std::cout << "Decoder input adjustment";
		std::cout << ": Phase " << complex_adjust->get_phase();
		std::cout << "; Conj " << complex_adjust->get_conj();
		std::cout << "; Depuncture alignment " << dropped << std::endl;
*/
	}
}

bool dvb_depuncture_viterbi_cb::next_conj()
{
	complex_adjust->set_conj(!complex_adjust->get_conj());
	return !complex_adjust->get_conj();
}

bool dvb_depuncture_viterbi_cb::next_phase()
{
	complex_adjust->set_phase((complex_adjust->get_phase() + 1) % 4);
	return complex_adjust->get_phase() == 0;
}

bool dvb_depuncture_viterbi_cb::next_alignment()
{
	drop->drop_next();
	dropped = (dropped + 1) % alignment_boundaries;
	return dropped == 0;
}

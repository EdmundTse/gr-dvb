#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "dvb_freqcorrect_cc.h"

dvb_freqcorrect_cc_sptr dvb_make_freqcorrect_cc(float alpha)
{
	return dvb_freqcorrect_cc_sptr(new dvb_freqcorrect_cc(alpha));
}

dvb_freqcorrect_cc::dvb_freqcorrect_cc(float alpha)
	: gr_sync_block("freqcorrect_cc",
			gr_make_io_signature(1, 1, sizeof(gr_complex)),
			gr_make_io_signature(1, 1, sizeof(gr_complex))),
			d_alpha(alpha), d_phase(0.0),
			d_sum(0.0), d_prev(0.0) {}

int dvb_freqcorrect_cc::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const gr_complex *in = (const gr_complex *) input_items[0];
	gr_complex *out = (gr_complex *) output_items[0];

	for (int i = 0; i < noutput_items; ++i)
	{
		d_sum = d_sum * gr_complex(1.0 - d_alpha, 0.0) + gr_complex(d_alpha, 0.0) * (in[i] * d_prev);
		d_prev = std::conj(in[i]);
		d_phase -= std::arg(d_sum);

		while (d_phase > 2 * M_PI)
		{
			d_phase -= 2 * M_PI;
		}
		while (d_phase < -2 * M_PI)
		{
			d_phase += 2 * M_PI;
		}
		out[i] = in[i] * gr_expj(d_phase);
	}
	
	// Tell runtime system how many output items we produced.
	return noutput_items;
}

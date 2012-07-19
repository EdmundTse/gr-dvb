#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "dvb_complex_adjust_cc.h"

// Define the four 90 degree phase rotations as complex multiplers
static const gr_complex phase[4] = { gr_complex(1), gr_complex(0,1), gr_complex(-1), gr_complex(0,-1) };

dvb_complex_adjust_cc_sptr dvb_make_complex_adjust_cc()
{
	return dvb_complex_adjust_cc_sptr(new dvb_complex_adjust_cc());
}

dvb_complex_adjust_cc::dvb_complex_adjust_cc()
	: gr_sync_block("complex_adjust_cc",
			gr_make_io_signature(1, 1, sizeof(gr_complex)),
			gr_make_io_signature(1, 1, sizeof(gr_complex))),
	conjugate(false),
	rotate_90(0) {}

int dvb_complex_adjust_cc::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const gr_complex *in = (const gr_complex *) input_items[0];
	gr_complex *out = (gr_complex *) output_items[0];

	// This inversion of checking conjugate flag first is for speed
	if (conjugate)
	{
		for (int i = 0; i < noutput_items; ++i)
		{
			out[i] = conj(in[i]) * phase[rotate_90];
		}
	}
	else
	{
		for (int i = 0; i < noutput_items; ++i)
		{
			out[i] = in[i] * phase[rotate_90];
		}
	}

	// Tell runtime system how many output items we produced.
	return noutput_items;
}

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "dvb_complex_to_interleaved_float.h"

dvb_complex_to_interleaved_float_sptr dvb_make_complex_to_interleaved_float()
{
	return dvb_complex_to_interleaved_float_sptr(new dvb_complex_to_interleaved_float());
}

dvb_complex_to_interleaved_float::dvb_complex_to_interleaved_float()
	: gr_sync_interpolator ("dvb_complex_to_interleaved_float",
		gr_make_io_signature(1, 1, sizeof(gr_complex)),
		gr_make_io_signature(1, 1, sizeof(float)),
		2) {}

int dvb_complex_to_interleaved_float::work(int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items)
{
	const gr_complex *in = (const gr_complex *) input_items[0];
	float *out = (float *) output_items[0];

	for (int i = 0; i < noutput_items / 2; ++i)
	{
		*out++ = in[i].real();
		*out++ = in[i].imag();
	}

	return noutput_items;
}




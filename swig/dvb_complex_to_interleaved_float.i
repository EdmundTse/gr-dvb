GR_SWIG_BLOCK_MAGIC(dvb, complex_to_interleaved_float);

dvb_complex_to_interleaved_float_sptr dvb_make_complex_to_interleaved_float();

class dvb_complex_to_interleaved_float : public gr_sync_interpolator
{
    private:
        dvb_complex_to_interleaved_float();
    public:
        ~dvb_complex_to_interleaved_float();
};

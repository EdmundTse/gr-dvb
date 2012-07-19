GR_SWIG_BLOCK_MAGIC(dvb, freqcorrect_cc);

dvb_freqcorrect_cc_sptr dvb_make_freqcorrect_cc(float alpha);

class dvb_freqcorrect_cc : public gr_sync_block
{
private:
    dvb_freqcorrect_cc(float alpha);
public:
    ~dvb_freqcorrect_cc();
};

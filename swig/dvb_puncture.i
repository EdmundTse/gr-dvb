/* Need to use std::vector<int> rather than gr_vector_int for SWIG type map */

GR_SWIG_BLOCK_MAGIC(dvb, puncture_bb);

dvb_puncture_bb_sptr dvb_make_puncture_bb(std::vector<int> sequence);

class dvb_puncture_bb : public gr_block
{
    private:
        dvb_puncture_bb(std::vector<int> sequence);
    public:
        ~dvb_puncture_bb();
};

// -----------------------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(dvb, depuncture_ff);

dvb_depuncture_ff_sptr dvb_make_depuncture_ff(std::vector<int> sequence);

class dvb_depuncture_ff : public gr_block
{
    private:
        dvb_depuncture_ff(std::vector<int> sequence);
    public:
        ~dvb_depuncture_ff();
};

GR_SWIG_BLOCK_MAGIC(dvb, depuncture_viterbi_cb);

dvb_depuncture_viterbi_cb_sptr dvb_make_depuncture_viterbi_cb(std::vector<int> sequence);

class dvb_depuncture_viterbi_cb : public gr_hier_block2
{
private:
    dvb_depuncture_viterbi_cb(std::vector<int> sequence);
public:
    ~dvb_depuncture_viterbi_cb();
};

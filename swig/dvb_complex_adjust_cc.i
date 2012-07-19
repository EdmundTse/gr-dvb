GR_SWIG_BLOCK_MAGIC(dvb, complex_adjust_cc);

dvb_complex_adjust_cc_sptr dvb_make_complex_adjust_cc();

class dvb_complex_adjust_cc : public gr_sync_block
{
    private:
        dvb_complex_adjust_cc();
    public:
        ~dvb_complex_adjust_cc();
        bool get_conj() const;
        void set_conj(const bool c);
        int get_phase() const;
        void set_phase(const int rotations);
};

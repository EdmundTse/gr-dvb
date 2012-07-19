GR_SWIG_BLOCK_MAGIC(dvb, randomizer_pp);

dvb_randomizer_pp_sptr dvb_make_randomizer_pp();

class dvb_randomizer_pp : public gr_sync_block
{
private:
    dvb_randomizer_pp();
public:
    ~dvb_randomizer_pp();
};

// -----------------------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(dvb, derandomizer_pp);

dvb_derandomizer_pp_sptr dvb_make_derandomizer_pp();

class dvb_derandomizer_pp : public gr_sync_block
{
private:
    dvb_derandomizer_pp();
public:
    ~dvb_derandomizer_pp();
};

GR_SWIG_BLOCK_MAGIC(dvb, rs_encoder_pp);

dvb_rs_encoder_pp_sptr dvb_make_rs_encoder_pp();

class dvb_rs_encoder_pp : public gr_sync_block
{
private:
    dvb_rs_encoder_pp();
public:
    ~dvb_rs_encoder_pp();
};

// -----------------------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(dvb, rs_decoder_pp);

dvb_rs_decoder_pp_sptr dvb_make_rs_decoder_pp();

class dvb_rs_decoder_pp : public gr_sync_block
{
private:
    dvb_rs_decoder_pp();
public:
    ~dvb_rs_decoder_pp();
};


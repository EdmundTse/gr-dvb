GR_SWIG_BLOCK_MAGIC(dvb, sync_decoder);

dvb_sync_decoder_sptr dvb_make_sync_decoder();

class dvb_sync_decoder : public gr_block
{
    private:
        dvb_sync_decoder();
    public:
        ~dvb_sync_decoder();
};

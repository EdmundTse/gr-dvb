GR_SWIG_BLOCK_MAGIC(dvb, fifo_shift_register_bb);

dvb_fifo_shift_register_bb_sptr dvb_make_fifo_shift_register_bb(size_t length);

class dvb_fifo_shift_register_bb : public gr_sync_block
{
private:
    dvb_fifo_shift_register_bb(size_t length);
public:
    ~dvb_fifo_shift_register_bb();
};


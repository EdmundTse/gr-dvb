GR_SWIG_BLOCK_MAGIC(dvb, drop);

dvb_drop_sptr dvb_make_drop(size_t item_size);

class dvb_drop : public gr_block
{
    private:
        dvb_drop(size_t item_size);
    public:
        ~dvb_drop();
        void drop_next();
};

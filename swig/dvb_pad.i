GR_SWIG_BLOCK_MAGIC(dvb, pad_mpeg_ts_packet_bp);

dvb_pad_mpeg_ts_packet_bp_sptr dvb_make_pad_mpeg_ts_packet_bp();

class dvb_pad_mpeg_ts_packet_bp : public gr_sync_decimator
{
private:
    dvb_pad_mpeg_ts_packet_bp();
public:
    ~dvb_pad_mpeg_ts_packet_bp();
};

// -----------------------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(dvb, depad_mpeg_ts_packet_pb);

dvb_depad_mpeg_ts_packet_pb_sptr dvb_make_depad_mpeg_ts_packet_pb();

class dvb_depad_mpeg_ts_packet_pb : public gr_sync_interpolator
{
private:
    dvb_depad_mpeg_ts_packet_pb();
public:
    ~dvb_depad_mpeg_ts_packet_pb();
};

// -----------------------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(dvb, pad_dvb_packet_rs_encoded_bp);

dvb_pad_dvb_packet_rs_encoded_bp_sptr dvb_make_pad_dvb_packet_rs_encoded_bp();

class dvb_pad_dvb_packet_rs_encoded_bp : public gr_sync_decimator
{
private:
    dvb_pad_dvb_packet_rs_encoded_bp();
public:
    ~dvb_pad_dvb_packet_rs_encoded_bp();
};

// -----------------------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(dvb, depad_dvb_packet_rs_encoded_pb);

dvb_depad_dvb_packet_rs_encoded_pb_sptr dvb_make_depad_dvb_packet_rs_encoded_pb();

class dvb_depad_dvb_packet_rs_encoded_pb : public gr_sync_interpolator
{
private:
    dvb_depad_dvb_packet_rs_encoded_pb();
public:
    ~dvb_depad_dvb_packet_rs_encoded_pb();
};

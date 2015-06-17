/*
 * Copyright (c) 2010 Edmund Tse
 *               2015 Santiago Piccinini
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "pad_mpeg_ts_packet_bp_impl.h"

namespace gr {
  namespace dvb {

    pad_mpeg_ts_packet_bp::sptr
    pad_mpeg_ts_packet_bp::make()
    {
      return gnuradio::get_initial_sptr
        (new pad_mpeg_ts_packet_bp_impl());
    }

    /*
     * The private constructor
     */
    pad_mpeg_ts_packet_bp_impl::pad_mpeg_ts_packet_bp_impl()
      : gr::sync_decimator("pad_mpeg_ts_packet_bp",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(mpeg_ts_packet)), MPEG_TS_PKT_LENGTH)
    {}

    /*
     * Our virtual destructor.
     */
    pad_mpeg_ts_packet_bp_impl::~pad_mpeg_ts_packet_bp_impl()
    {
    }

    void
    pad_mpeg_ts_packet_bp_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required)
    {
        unsigned ninputs = ninput_items_required.size();
        for (unsigned i = 0; i < ninputs; ++i)
        {
            ninput_items_required[i] = noutput_items * MPEG_TS_PKT_LENGTH;

        }
    }

    int
    pad_mpeg_ts_packet_bp_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const unsigned char *in = (const unsigned char *) input_items[0];
        mpeg_ts_packet *out = (mpeg_ts_packet *) output_items[0];

        for (int i = 0; i < noutput_items; ++i)
        {
            std::memcpy(out[i].data, &in[i * MPEG_TS_PKT_LENGTH], MPEG_TS_PKT_LENGTH);
        }

        return noutput_items;
    }

  } /* namespace dvb */
} /* namespace gr */


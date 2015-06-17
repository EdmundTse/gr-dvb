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

#ifndef INCLUDED_DVB_DEPUNCTURE_VITERBI_CB_IMPL_H
#define INCLUDED_DVB_DEPUNCTURE_VITERBI_CB_IMPL_H

#include <dvb/depuncture_viterbi_cb.h>
#include <algorithm>
#include <cassert>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <gnuradio/trellis/fsm.h>
#include <gnuradio/blocks/interleave.h>
#include <gnuradio/trellis/metrics_f.h>
#include <gnuradio/trellis/viterbi_b.h>
#include "gnuradio/digital/metric_type.h"
#include "dvb/complex_adjust_cc.h"
#include "dvb/complex_to_interleaved_float.h"
#include "dvb/drop.h"
#include "dvb/depuncture_ff.h"
#include "dvb/sync_decoder.h"
#include "dvb_consts.h"


namespace gr {
  namespace dvb {

    class depuncture_viterbi_cb_impl : public depuncture_viterbi_cb
    {
     private:
        //friend dvb_depuncture_viterbi_cb_sptr dvb_make_depuncture_viterbi_cb(gr_vector_int sequence);
        unsigned int dropped;
        unsigned int alignment_boundaries;

        bool next_conj();
        bool next_phase();
        bool next_alignment();

        // Sub blocks
        gr::dvb::complex_adjust_cc::sptr complex_adjust;
        gr::dvb::drop::sptr drop;
        gr::dvb::complex_to_interleaved_float::sptr c2f;
        gr::dvb::depuncture_ff::sptr depuncture;
        gr::trellis::metrics_f::sptr metrics;
        gr::trellis::viterbi_b::sptr viterbi;
        gr::dvb::sync_decoder::sptr sync_decoder;

     public:
      depuncture_viterbi_cb_impl(const std::vector<int> &sequence);
      ~depuncture_viterbi_cb_impl();

      void sync_decoder_callback(bool is_locked);

      // Where all the action really happens
    };

  } // namespace dvb
} // namespace gr

#endif /* INCLUDED_DVB_DEPUNCTURE_VITERBI_CB_IMPL_H */


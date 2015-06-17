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

#ifndef INCLUDED_DVB_RS_IMPL_H
#define INCLUDED_DVB_RS_IMPL_H

#include <cassert>
#include "dvb_consts.h"
#include "dvb_types.h"

extern "C"
{
	#include <gnuradio/fec/rs.h>
}

/*!
 * \brief DVB Reed-Solomon encoder/decoder
 *
 * RS(204,188,T=8) shortened code.
 */
namespace gr {
  namespace dvb {
    class dvb_rs
    {
        private:
            void *rs;		// RS characteristics structure

        public:
            dvb_rs();
            ~dvb_rs();

            /*!
             * \brief Add RS error correction encoding
             */
            void encode(dvb_packet_rs_encoded &out, const mpeg_ts_packet &in);

            /*!
             * \brief Decodes RS encoded packet.
             * \returns a count of corrected symbols, or -1 if the block was uncorrectible.
             */
            int decode(mpeg_ts_packet &out, const dvb_packet_rs_encoded &in);
    };
  } // namespace dvb
} // namespace gr
#endif /* INCLUDED_DVB_RS_IMPL_H */

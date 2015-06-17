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
 
#ifndef INCLUDED_DVB_RANDOMIZER_IMPL_H
#define INCLUDED_DVB_RANDOMIZER_IMPL_H

#include <cassert>
#include "dvb_consts.h"
#include "dvb_types.h"

namespace gr {
  namespace dvb {

    /*!
     * \brief DVB data randomiser implementation
     * \ingroup dvb
     */

    class dvb_randomizer
    {
        private:
            unsigned int counter;
            static const unsigned int PRELOAD_VALUE = 0x4a80;	// '100101010000000'
            unsigned char sequence[DVB_RANDOMIZER_PERIOD];		// The sequence to XOR with

            friend class qa_dvb_randomizer;

        public:
            __attribute__ ((visibility ("default"))) dvb_randomizer();
            virtual ~dvb_randomizer() {}

            //! Resets randomiser LFSR
            void reset();

            //! Whitens an MPEG TS packet
            __attribute__ ((visibility ("default"))) void randomize(mpeg_ts_packet &out, const mpeg_ts_packet &in);
            //! De-whiten a randomised MPEG TS packet
            __attribute__ ((visibility ("default"))) void derandomize(mpeg_ts_packet &out, const mpeg_ts_packet &in);
    };
  } // namespace dvb
} // namespace gr
#endif /* INCLUDED_DVB_RANDOMIZER_IMPL_H */

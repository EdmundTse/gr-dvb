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
#include <config.h>
#endif

#include "dvb_randomizer.h"
#include <iostream>

namespace gr {
  namespace dvb {

    dvb_randomizer::dvb_randomizer() :
        counter(0)
    ///	current_state(PRELOAD_VALUE)
    {
        // Generate and store the PRBS
        unsigned int state = PRELOAD_VALUE;
        unsigned char bit, byte;
        for (int i = 1; i < DVB_RANDOMIZER_PERIOD; ++i)
        {
            assert(state < 1 << 15);
            byte = 0;
            // Calculate the next byte output
            for (int j = 0; j < 8; ++j)
            {
                // Append the next LFSR output to LSB of output
                byte <<= 1;
                bit = (state & 0x0002) >> 1 ^ state & 0x0001;
                byte |= bit;
                // Shift the LFSR bits by 1 and feed output bit back to the start
                state >>= 1;
                state |= bit << 14;
            }
            sequence[i] = byte;
        }
        // First SYNC is inverted
        sequence[0] = 0xFF;
        // Disable PRBS for subsequent SYNCs to leave untouched
        for (int i = MPEG_TS_PKT_LENGTH; i < DVB_RANDOMIZER_PERIOD; i += MPEG_TS_PKT_LENGTH)
        {
            sequence[i] = 0x00;
        }
    }

    void dvb_randomizer::reset()
    {
        counter = 0;
    }

    void dvb_randomizer::randomize(mpeg_ts_packet &out, const mpeg_ts_packet &in)
    {
        for (int i = 0; i < MPEG_TS_PKT_LENGTH; ++i)
        {
            out.data[i] = in.data[i] ^ sequence[counter];
            counter = (counter + 1) % DVB_RANDOMIZER_PERIOD;
        }
    }

    void dvb_randomizer::derandomize(mpeg_ts_packet &out, const mpeg_ts_packet &in)
    {
        // Synchronise to inverted SYNC byte
        if (in.data[0] == MPEG_TS_SYNC_BYTE_INV)
        {
            reset();
        }

        // Equivalent to randomisation
        randomize(out, in);
    }

  } /* namespace dvb */
} /* namespace gr */

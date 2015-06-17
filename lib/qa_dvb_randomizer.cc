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

#include "qa_dvb_randomizer.h"

namespace gr {
  namespace dvb {
    /* Not used anymore, but keeping this for reference
    static unsigned int EXPECTED_INITIAL_STATES[] =
    {
        0x4A80, 0x604A, 0x37E0, 0x0837, 0x1608, 0x0616, 0x0E86, 0x628E,
        0x64E2, 0x49E4, 0x0B49, 0x768B, 0x6776, 0x66E7, 0x4A66, 0x2ACA,
        0x57AA, 0x3FD7, 0x1E3F, 0x101E, 0x0890, 0x6C08, 0x066C, 0x2D06,
        0x42AD, 0x7DC2, 0x11FD, 0x0191, 0x2C81, 0x60AC, 0x7D60, 0x687D,
        0x21E8, 0x0E21, 0x188E, 0x6498, 0x6A64, 0x2B6A, 0x6FAB, 0x3F6F,
        0x6C3F, 0x106C, 0x2D10, 0x4C2D, 0x1DCC, 0x151D, 0x4995, 0x2FC9,
        0x16AF, 0x7C16, 0x0EFC, 0x410E, 0x44C1, 0x50C4, 0x5350, 0x7C53,
        0x3D7C, 0x613D, 0x51E1, 0x08D1, 0x5C88, 0x665C, 0x3966, 0x6AB9
    };
    */

    static unsigned char EXPECTED_INITIAL_VALUES[] =
    {
        0x03, 0xF6, 0x08, 0x34, 0x30, 0xB8, 0xA3, 0x93,
        0xC9, 0x68, 0xB7, 0x73, 0xB3, 0x29, 0xAA, 0xF5,
        0xFE, 0x3C, 0x04, 0x88, 0x1B, 0x30, 0x5A, 0xA1,
        0xDF, 0xC4, 0xC0, 0x9A, 0x83, 0x5F, 0x0B, 0xC2,
        0x38, 0x8C, 0x93, 0x2B, 0x6A, 0xFB, 0x7E, 0x1B,
        0x04, 0x5A, 0x19, 0xDC, 0x54, 0xC9, 0xFA, 0xB4,
        0x1F, 0xB8, 0x41, 0x91, 0x85, 0x65, 0x1F, 0x5E,
        0x43, 0xC5, 0x88, 0x9D, 0x33, 0x4E, 0xAB, 0xA7,
        0xF9, 0xD0, 0x14, 0xE0, 0x7A, 0x41, 0x1D, 0x86,
        0x4D, 0x15, 0xAE, 0x7D, 0xE5, 0x0C, 0x5E, 0x29
    };

    #define NELEMENTS(ary) (sizeof(ary) / sizeof(ary[0]))

    void qa_dvb_randomizer::setUp() {}
    void qa_dvb_randomizer::tearDown() {}

    void qa_dvb_randomizer::lfsr_start_values()
    {
        // LFSR should start with expected values
        unsigned char value;
        for (unsigned int i = 0; i < NELEMENTS(EXPECTED_INITIAL_VALUES); ++i)
        {
            CPPUNIT_ASSERT_EQUAL((unsigned int) EXPECTED_INITIAL_VALUES[i], (unsigned int) randomizer.sequence[i+1]);
        }
    }

    /*
     * Checks that the derandomiser is indeed the inverse operation of the randomiser
     */
    void qa_dvb_randomizer::test_randomize_derandomize()
    {
        dvb_randomizer derandomizer;

        // Create 100 random MPEG packets
        mpeg_ts_packet src_data[100], randomized_data[100], dst_data[100];
        for (int i = 0; i < 100; ++i)
        {
            src_data[i].data[0] = MPEG_TS_SYNC_BYTE;
            for (int j = 1; j < MPEG_TS_PKT_LENGTH; ++j)
            {
                src_data[i].data[j] = rand() % 256;
            }
        }

        // Randomise them
        for (int i = 0; i < 100; ++i)
        {
            randomizer.randomize(randomized_data[i], src_data[i]);
        }

        // Check sync bytes of the randomised packets
        for (int i = 0; i < 100; ++i)
        {
            if (i % DVB_RANDOMIZER_INVERTED_SYNC_PERIOD == 0)
            {
                CPPUNIT_ASSERT_EQUAL(MPEG_TS_SYNC_BYTE_INV, randomized_data[i].data[0]);
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(MPEG_TS_SYNC_BYTE, randomized_data[i].data[0]);
            }
        }

        // Derandomise the randomised packets
        for (int i = 0; i < 100; ++i)
        {
            derandomizer.derandomize(dst_data[i], randomized_data[i]);
        }

        // Check derandomised packets
        for (int i = 0; i < 100; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(MPEG_TS_SYNC_BYTE, dst_data[i].data[0]);

            for (int j = 1; j < MPEG_TS_PKT_LENGTH; ++j)
            {
                CPPUNIT_ASSERT_EQUAL(src_data[i].data[j], dst_data[i].data[j]);
            }
        }
    }

  } // namespace dvb
} // namespace gr

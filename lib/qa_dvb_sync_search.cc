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

#include "qa_dvb_sync_search.h"
#include <cstdlib>	// for random()
#include <vector>

namespace gr {
  namespace dvb {

    std::vector<bool> random_bits(int length)
    {
        std::vector<bool> sequence(length);
        for (std::vector<bool>::iterator it = sequence.begin(); it != sequence.end(); ++it)
        {
            *it = random() % 2;
        }
        return sequence;
    }

    void qa_dvb_sync_search::setUp() {}
    void qa_dvb_sync_search::tearDown() {}

    /*
     * The sync searcher shouldn't lock onto random noise
     */
    void qa_dvb_sync_search::test_sync_noise()
    {
        // Generate a pseudo-random sequence
        std::vector<bool> sequence = random_bits(100000);

        // Feed this sequence into the sync searcher.
        for (std::vector<bool>::iterator it = sequence.begin(); it != sequence.end(); ++it)
        {
            // Should remain unlocked and never trigger an output
            CPPUNIT_ASSERT(!sync_search.process(*it));
            CPPUNIT_ASSERT_EQUAL(dvb_sync_search::Unlocked, sync_search.mode());
        }
    }

    /*
     * The minimum sequence for the sync searcher to lock onto
     */
    void qa_dvb_sync_search::test_sync_lock()
    {
        // The sync searcher should start in an Unlocked state.
        CPPUNIT_ASSERT_EQUAL(dvb_sync_search::Unlocked, sync_search.mode());

        // To get the sync searcher to lock, we first need to give it 4 consecutive SYNCs
        for (int i = 0; i < CONFIDENCE_THRESHOLD; ++i)
        {
            // Put in a SYNC byte
            for (int j = 7; j >= 0; --j)
                CPPUNIT_ASSERT(!sync_search.process((MPEG_TS_SYNC_BYTE & 1<<j) >> j));

            // Now fill the other 203 bytes
            for (int j = 0; j < (DVB_RS_ENCODED_LENGTH-1)*8; ++j)
                CPPUNIT_ASSERT(!sync_search.process(0));
        }

        // The sync searcher should have locked and would then begin to seek to the next inverted SYNC bits
        CPPUNIT_ASSERT_EQUAL(dvb_sync_search::Seeking, sync_search.mode());

        // Put the first 7 of the inverted SYNC bits into the sync searcher.
        for (int i = 7; i > 0; --i)
            CPPUNIT_ASSERT(!sync_search.process((MPEG_TS_SYNC_BYTE_INV & 1<<i) >> i));
        // On the last inverted SYNC bit, the sync searcher should be synced and want to make an output
        CPPUNIT_ASSERT(sync_search.process(MPEG_TS_SYNC_BYTE_INV & 1));
        CPPUNIT_ASSERT_EQUAL(dvb_sync_search::Synced, sync_search.mode());
        CPPUNIT_ASSERT_EQUAL(CONFIDENCE_THRESHOLD, sync_search.cl);

        // Test correct alignment of checking the next sync byte
        for (int i = 0; i < DVB_RS_ENCODED_LENGTH; ++i)
        {
            for (int j = 0; j < 7; ++j)
                CPPUNIT_ASSERT(!sync_search.process(0));
            CPPUNIT_ASSERT(sync_search.process(0));
        }
        CPPUNIT_ASSERT_EQUAL(CONFIDENCE_THRESHOLD - 1, sync_search.cl);	// Less 1 since we missed one

        // This time let's regain confidence by giving a real SYNC byte
        for (int i = 0; i < DVB_RS_ENCODED_LENGTH - 1; ++i)
        {
            for (int j = 0; j < 7; ++j)
                CPPUNIT_ASSERT(!sync_search.process(0));
            CPPUNIT_ASSERT(sync_search.process(0));
        }
        for (int i = 7; i >= 0; --i)
        {
            sync_search.process((MPEG_TS_SYNC_BYTE_INV & 1<<i) >> i);
        }
        CPPUNIT_ASSERT_EQUAL(CONFIDENCE_THRESHOLD, sync_search.cl);
    }

  } // namespace dvb
} // namespace gr

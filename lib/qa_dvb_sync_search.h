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

#ifndef INCLUDED_QA_DVB_SYNC_SEARCH_IMPL_H
#define INCLUDED_QA_DVB_SYNC_SEARCH_IMPL_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestAssert.h>

#include "dvb_sync_search.h"

namespace gr {
  namespace dvb {

    class qa_dvb_sync_search : public CppUnit::TestCase
    {
    private:
        dvb_sync_search sync_search;
        void test_sync_noise();
        void test_sync_lock();

    public:
        void setUp();
        void tearDown();
        CPPUNIT_TEST_SUITE(qa_dvb_sync_search);
        CPPUNIT_TEST(test_sync_noise);
        CPPUNIT_TEST(test_sync_lock);
        CPPUNIT_TEST_SUITE_END();
    };

  } // namespace dvb
} // namespace gr

#endif /* INCLUDED_QA_DVB_SYNC_SEARCH_IMPL_H */

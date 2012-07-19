#ifndef INCLUDED_QA_DVB_SYNC_SEARCH_IMPL_H
#define INCLUDED_QA_DVB_SYNC_SEARCH_IMPL_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestAssert.h>

#include "dvb_sync_search_impl.h"
#include "qa_dvb_utils.h"

class qa_dvb_sync_search_impl : public CppUnit::TestCase
{
private:
	dvb_sync_search sync_search;
	void test_sync_noise();
	void test_sync_lock();

public:
	void setUp();
	void tearDown();
	CPPUNIT_TEST_SUITE(qa_dvb_sync_search_impl);
	CPPUNIT_TEST(test_sync_noise);
	CPPUNIT_TEST(test_sync_lock);
	CPPUNIT_TEST_SUITE_END();
};

#endif /* INCLUDED_QA_DVB_SYNC_SEARCH_IMPL_H */

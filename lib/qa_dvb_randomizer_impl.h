#ifndef INCLUDED_QA_DVB_RANDOMIZER_PP_H
#define INCLUDED_QA_DVB_RANDOMIZER_PP_H

#include <cstdlib>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestAssert.h>

#include "dvb_randomizer_impl.h"

class qa_dvb_randomizer_pp : public CppUnit::TestCase
{
private:
	dvb_randomizer randomizer;
	void lfsr_start_values();
	void test_randomize_derandomize();

public:
	void setUp();
	void tearDown();
	CPPUNIT_TEST_SUITE(qa_dvb_randomizer_pp);
	CPPUNIT_TEST(lfsr_start_values);
	CPPUNIT_TEST(test_randomize_derandomize);
	CPPUNIT_TEST_SUITE_END();
};

#endif /* INCLUDED_QA_DVB_RANDOMIZER_PP_H */

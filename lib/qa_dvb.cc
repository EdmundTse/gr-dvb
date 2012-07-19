#include <qa_dvb.h>

/*
 * This test suite contains all of the test classes written in CPPUnit
 */
CppUnit::TestSuite *qa_dvb::suite()
{
	CppUnit::TestSuite *s = new CppUnit::TestSuite("dvb");

	s->addTest(qa_dvb_randomizer_pp::suite());
	s->addTest(qa_dvb_sync_search_impl::suite());

	return s;
}

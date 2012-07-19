#ifndef INCLUDED_QA_DVB_H
#define INCLUDED_QA_DVB_H

#include <cppunit/TestSuite.h>
#include "qa_dvb_randomizer_impl.h"
#include "qa_dvb_sync_search_impl.h"

//! collect all the tests for the example directory

class qa_dvb
{
public:
	//! return suite of tests for all of example directory
	static CppUnit::TestSuite *suite();
};

#endif /* INCLUDED_QA_DVB_H */

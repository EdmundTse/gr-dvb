#include <cppunit/TextTestRunner.h>

#include <qa_dvb.h>

int main (int argc, char **argv)
{  
	CppUnit::TextTestRunner runner;
	runner.addTest(qa_dvb::suite());
	bool was_successful = runner.run("", false);
	return was_successful ? 0 : 1;
}

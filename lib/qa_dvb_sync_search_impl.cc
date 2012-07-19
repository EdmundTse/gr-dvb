#include "qa_dvb_sync_search_impl.h"

void qa_dvb_sync_search_impl::setUp() {}
void qa_dvb_sync_search_impl::tearDown() {}

/*
 * The sync searcher shouldn't lock onto random noise
 */
void qa_dvb_sync_search_impl::test_sync_noise()
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
void qa_dvb_sync_search_impl::test_sync_lock()
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

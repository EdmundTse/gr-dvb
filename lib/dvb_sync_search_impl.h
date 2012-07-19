#ifndef INCLUDED_DVB_SYNC_SEARCH_IMPL_H
#define INCLUDED_DVB_SYNC_SEARCH_IMPL_H

#include <cassert>
#include <iostream>
#include "dvb_consts.h"

/*!
 * \brief DVB data randomiser implementation
 * \ingroup dvb
 */
class dvb_sync_search
{
	public:
		enum Mode { Unlocked, Seeking, Synced };

	private:
		Mode _mode;
		unsigned char buffer;	// Byte buffer to store bits as they come in
		int cl;					// Confidence level of synchronisation
		int fast_forward;		// Number of input bits until we process the input
		int counter;			// Counts the number of bytes that was output so far
		friend class qa_dvb_sync_search_impl;

	public:
		dvb_sync_search();
		virtual ~dvb_sync_search() {}

		//! Resets the sync searcher to its initial state
		void reset();

		//! Processes an incoming bit, and returns true if it triggers an output
		bool process(const unsigned char &input);

		//! Returns the sync searcher operation mode
		inline Mode mode() const { return _mode; }

		//! Returns the confidence level
		inline int confidence() const { return cl; }

		//! Outputs the contents of the byte buffer
		inline unsigned char output() const { return buffer; }
};

#endif /* INCLUDED_DVB_SYNC_SEARCH_IMPL_H */

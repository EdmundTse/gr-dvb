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

#ifndef INCLUDED_DVB_SYNC_SEARCH_IMPL_H
#define INCLUDED_DVB_SYNC_SEARCH_IMPL_H

#include <cassert>
#include <iostream>
#include "dvb_consts.h"

namespace gr {
    namespace dvb {
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
            friend class qa_dvb_sync_search;

        public:
            __attribute__ ((visibility ("default"))) dvb_sync_search();
            virtual ~dvb_sync_search() {}

            //! Resets the sync searcher to its initial state
            void reset();

            //! Processes an incoming bit, and returns true if it triggers an output
            __attribute__ ((visibility ("default"))) bool process(const unsigned char &input);

            //! Returns the sync searcher operation mode
            inline Mode mode() const { return _mode; }

            //! Returns the confidence level
            inline int confidence() const { return cl; }

            //! Outputs the contents of the byte buffer
            inline unsigned char output() const { return buffer; }
    };

  } // namespace dvb
} // namespace gr
#endif /* INCLUDED_DVB_SYNC_SEARCH_IMPL_H */

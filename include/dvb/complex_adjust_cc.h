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


#ifndef INCLUDED_DVB_COMPLEX_ADJUST_CC_H
#define INCLUDED_DVB_COMPLEX_ADJUST_CC_H

#include <dvb/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace dvb {

    /*!
     * \brief <+description of block+>
     * \ingroup dvb
     *
     */
    class DVB_API complex_adjust_cc : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<complex_adjust_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of dvb::complex_adjust_cc.
       *
       * To avoid accidental use of raw pointers, dvb::complex_adjust_cc's
       * constructor is in a private implementation
       * class. dvb::complex_adjust_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make();

      virtual bool get_conj() const = 0;
      virtual void set_conj(const bool) = 0;
      virtual int get_phase() const = 0;
      virtual void set_phase(const int) = 0;
    };
  } // namespace dvb
} // namespace gr

#endif /* INCLUDED_DVB_COMPLEX_ADJUST_CC_H */


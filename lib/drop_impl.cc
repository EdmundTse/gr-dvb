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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "drop_impl.h"

namespace gr {
  namespace dvb {

    drop::sptr
    drop::make(size_t item_size)
    {
      return gnuradio::get_initial_sptr
        (new drop_impl(item_size));
    }

    /*
     * The private constructor
     */
    drop_impl::drop_impl(size_t item_size)
      : gr::block("drop",
              gr::io_signature::make(1, 1, item_size),
              gr::io_signature::make(1, 1, item_size)),
        drop_next_item(false)
    {}

    /*
     * Our virtual destructor.
     */
    drop_impl::~drop_impl()
    {
    }

    void
    drop_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        // We don't know how often we'd need to drop, we estimate 1 item needed per output
        std::fill(ninput_items_required.begin(), ninput_items_required.end(), noutput_items);
    }

    int
    drop_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const unsigned char *in = (const unsigned char *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];

        size_t item_size = input_signature()->sizeof_stream_item(0);
        int ni = 0;
        int no = 0;

        // Terminate when we run out of either input data or output capacity
        while (ni < ninput_items[0] && no < noutput_items)
        {
            if (drop_next_item)
            {
                drop_next_item = false;
            }
            else
            {
                std::memcpy(out, in, item_size);
                out += item_size;
                ++no;
            }
            in += item_size;
            ++ni;
        }

        consume_each(ni);
        return no;
    }

    void drop_impl::drop_next()
    {
        drop_next_item = true;
    }

  } /* namespace dvb */
} /* namespace gr */


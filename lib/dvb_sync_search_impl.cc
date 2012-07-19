#include "dvb_sync_search_impl.h"

dvb_sync_search::dvb_sync_search() :
	_mode(Unlocked), buffer(0), cl(0), fast_forward(1), counter(0) {}

void dvb_sync_search::reset()
{
	_mode = Unlocked;
	buffer = 0;
	cl = 0;
	fast_forward = 1;
	counter = 0;
}

bool dvb_sync_search::process(const unsigned char &input)
{
	assert(fast_forward >= 0);
	assert(cl >= 0 && cl <= CONFIDENCE_THRESHOLD);
	assert(counter >= 0 && counter < DVB_RS_ENCODED_LENGTH);

	bool have_output = false;

	// Read a bit into buffer
	buffer = (buffer << 1) | (input & 1);
	--fast_forward;

	if (fast_forward == 0)
	{
		switch (_mode)
		{
			case Unlocked:
				if (buffer == MPEG_TS_SYNC_BYTE)
				{
					if (++cl == CONFIDENCE_THRESHOLD)
					{
						_mode = Seeking;
						std::cout << "Sync decoder: Seeking inverted SYNC" << std::endl;
					}
					fast_forward = DVB_RS_ENCODED_LENGTH * 8;
				}
				else if (cl > 0)
				{
					// Still have some confidence in finding the next SYNC
					--cl;
					fast_forward = DVB_RS_ENCODED_LENGTH * 8;
				}
				else
				{
					fast_forward = 1;
				}
				break;
			case Seeking:
				if (buffer == MPEG_TS_SYNC_BYTE)
				{
					cl = CONFIDENCE_THRESHOLD;
					fast_forward = DVB_RS_ENCODED_LENGTH * 8;
				}
				else if (buffer == MPEG_TS_SYNC_BYTE_INV)
				{
					cl = CONFIDENCE_THRESHOLD;
					_mode = Synced;
					have_output = true;
					fast_forward = 8;	// Fast forward to next byte
					std::cout << "Sync decoder: Synced" << std::endl;
				}
				else
				{
					fast_forward = DVB_RS_ENCODED_LENGTH * 8;
					if (--cl == 0)
					{
						_mode = Unlocked;
						fast_forward = 1;
						std::cout << "Sync decoder: Unlocked" << std::endl;
					}
				}
				break;
			case Synced:
				// Output a byte and move to the next
				have_output = true;
				++counter;
				fast_forward = 8;		// Fast forward to next byte
				if (counter == DVB_RS_ENCODED_LENGTH)
				{
					counter = 0;
					if (buffer == MPEG_TS_SYNC_BYTE || buffer == MPEG_TS_SYNC_BYTE_INV)
					{
						cl = CONFIDENCE_THRESHOLD;
					}
					else
					{
						if (--cl == 0)
						{
							_mode = Unlocked;
							std::cout << "Sync decoder: Unlocked" << std::endl;
							fast_forward = 1;	// No longer synced, so read in bit by bit
						}
					}
				}
				break;
		}
	}
	return have_output;
}

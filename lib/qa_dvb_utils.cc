#include "qa_dvb_utils.h"

std::vector<bool> random_bits(int length)
{
	std::vector<bool> sequence(length);
	for (std::vector<bool>::iterator it = sequence.begin(); it != sequence.end(); ++it)
	{
		*it = random() % 2;
	}
	return sequence;
}

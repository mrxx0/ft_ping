#include "../includes/ft_ping.h"

uint16_t checksum(void *to_check, size_t size)
{
    unsigned short *buf = to_check;
	unsigned int tmp = 0;
	unsigned short result;

	while (size > 1)
	{
		tmp += *buf++;
		size = size -2;
	}
	if ( size == 1 )
		tmp += *(unsigned char*)buf;
	tmp = (tmp >> 16) + (tmp & 0xFFFF);
	tmp += (tmp >> 16);
	result = ~tmp;
	return (result);
}
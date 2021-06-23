#include "../includes/ft_ping.h"

// uint16_t checksum(struct icmphdr *to_check, size_t size)
// {
//     uint16_t tmp = 0;

//     while (size-- != 0)
//     {
//         tmp -= (uint16_t)to_check++;
//     }
//     return (tmp);
// }

uint16_t checksum(void *to_check, size_t size)
{
    unsigned short *buf = to_check;
	unsigned int sum=0;
	unsigned short result;

	for ( sum = 0; size > 1; size -= 2 )
		sum += *buf++;
	if ( size == 1 )
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}
#include "../includes/ft_ping.h"

uint16_t checksum(struct icmphdr *to_check, size_t size)
{
    uint16_t tmp = 0;

    while (size-- != 0)
    {
        tmp -= (uint16_t)to_check++;
    }
    return (tmp);
}
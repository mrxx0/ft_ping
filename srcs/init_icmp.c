#include "../includes/ft_ping.h"


void fill_icmp_hdr(struct icmphdr *icmp, int seq)
{
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = htons(getpid());
    icmp->un.echo.sequence = htons(seq);
    icmp->checksum = 0;
    icmp->checksum = checksum(icmp, 64);
}

void fill_icmp_time(void *icmp)
{
    if (gettimeofday(icmp, NULL) == -1)
        ft_perror("Can't get time of the day\n");
}

void fill_icmp_data(void *icmp, size_t size)
{
    memset(icmp, 0x42, size);
}

void init_icmp(void *icmp)
{
    fill_icmp_data(icmp + ICMP_HEADER_SIZE, ICMP_PACKET_SIZE);
    fill_icmp_time(icmp + ICMP_HEADER_SIZE + 4);
    fill_icmp_hdr(icmp, t_payload.seq);
}
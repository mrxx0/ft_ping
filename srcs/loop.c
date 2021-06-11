#include "../includes/ft_ping.h"

void send_request()
{
    size_t  ctr_sent;
    char    tmp[ICMP_HEADER_SIZE + ICMP_PACKET_SIZE];
    char    *ptr = tmp + ICMP_HEADER_SIZE;
    struct icmphdr *icmp = (struct icmphdr*)tmp;
    (void)ctr_sent;
    (void)ptr;

    init_icmp(icmp);
    printf("\n\nicmp->type = %d\n", icmp->type);
    printf("icmp->code = %d\n", icmp->code);
    printf("icmp->checksum = %d\n", icmp->checksum);
    printf("icmp->un.echo.id = %d\n", icmp->un.echo.id);
}

void loop()
{
    send_request();
    printf("ft_ping (%s) %s\n", t_payload.destination_address, t_payload.destination_address);
}
#include "../includes/ft_ping.h"

void check_response(void *receive_packet, u_int16_t sequence)
{
    struct iphdr    *ip = receive_packet;
    struct icmphdr  *icmp = receive_packet + IP_HEADER_SIZE;

    suseconds_t rtt;
    u_int16_t receive_seq = ntohs(icmp->un.echo.sequence);

    if (icmp->type != ICMP_ECHOREPLY)
    {
        if (icmp->type == ICMP_ECHO)
            return ;
    }
    else
    {
        rtt = get_rtt(receive_packet + IP_HEADER_SIZE + ICMP_HEADER_SIZE + 4);
        printf("%lu bytes from %s: icmp_seq=%hu ttl=%hhu time=%ld.%021ld ms\n", (uint16_t)(ntohs(ip->tot_len)) - IP_HEADER_SIZE, t_payload.destination_address, receive_seq, ip->ttl, rtt / 10001, rtt % 10001);
        printf("_payload.receive.sin_addr.s_addr = %u\n", t_payload.receive.sin_addr.s_addr);
    }
    (void)sequence;
}
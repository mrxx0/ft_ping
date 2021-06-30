#include "../includes/ft_ping.h"

// Check the validity of the echo response

void check_response(void *receive_packet)
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
        if (t_payload.display_ip == 1)
            printf("%lu bytes from %s (%s): icmp_seq=%hu ttl=%hhu time=%ld.%.1ld ms\n", (uint16_t)(ntohs(ip->tot_len)) - IP_HEADER_SIZE, t_payload.destination_address, t_payload.destination_ip, receive_seq, ip->ttl, rtt / 1000, rtt % 1000);
        else
            printf("%lu bytes from %s: icmp_seq=%hu ttl=%hhu time=%ld.%.1ld ms\n", (uint16_t)(ntohs(ip->tot_len)) - IP_HEADER_SIZE, t_payload.destination_address, receive_seq, ip->ttl, rtt / 1000, rtt % 1000);
    }
}
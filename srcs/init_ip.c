#include "../includes/ft_ping.h"

// Init the ip part of the packet

void fill_ip (struct iphdr *ip, uint32_t dst)
{
    ip->version = 4;
	ip->ihl = IP_HEADER_SIZE / 4;
	ip->tos = 0;
	ip->tot_len = ICMP_SIZE + IP_HEADER_SIZE;
	ip->id = 0;
	ip->frag_off = 0;
	ip->ttl = t_payload.ttl;
	ip->protocol = IPPROTO_ICMP;
	ip->check = 0;
	ip->saddr = INADDR_ANY;
	ip->daddr = dst;
}

void init_ip (void *ip, uint32_t dst)
{
    fill_ip(ip, dst);
}

#include "../includes/ft_ping.h"

struct s_payload t_payload = {
    .socket_fd = 0,
    .ttl = 64,
    .seq = 0,
    .opt = 0,
    .id_opt = 0,
    .timeout = 1,
    .destination_address = {0},
    .destination_ip = {0},
    .addr2 =
    {
        .sin_family = PF_INET,
        .sin_port = 0
    }
};

void fill_ip (struct iphdr *ip)
{
    ip->version = 4;
	ip->ihl = IP_HEADER_SIZE / 4;
	ip->tos = 0;
	ip->tot_len = htons(ICMP_PACKET_SIZE);
	ip->id = htons(0);
	ip->frag_off = htons(0);
	ip->ttl = t_payload.ttl;
	ip->protocol = IPPROTO_ICMP;
	ip->check = 0;
	ip->saddr = INADDR_ANY;
	ip->daddr = t_payload.addr2.sin_addr.s_addr;
}

void init_ip (void *ip)
{
    fill_ip(ip);
}

void fill_icmp_hdr(struct icmphdr *icmp)
{
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->checksum = checksum(icmp, 64);
    icmp->un.echo.id = htons(getpid());
    icmp->un.echo.sequence = htons(t_payload.seq);
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
    fill_icmp_hdr(icmp);
}

// Check if destination (host)

_Bool init_destination()
{
    struct addrinfo *addr = NULL;
    struct addrinfo tmp;
    tmp.ai_family = PF_INET;
    tmp.ai_socktype = SOCK_RAW;
    tmp.ai_protocol = IPPROTO_ICMP;

    if (getaddrinfo(t_payload.destination_address, NULL, &tmp, &addr) != EXIT_SUCCESS)
    {
        freeaddrinfo(addr);
        fprintf(stderr, "ft_ping : %s : Name or service not known\n", t_payload.destination_address);
        return (EXIT_FAILURE);
    }
    t_payload.addrlen = addr->ai_addrlen;
    ft_memcpy(&t_payload.addr, addr->ai_addr, sizeof(addr->ai_addr));
    // t_payload.addr2.sin_addr.s_addr = ((struct sockaddr_in*)addr->ai_addr)->sin_addr.s_addr;

    inet_ntop(addr->ai_family, &((struct sockaddr_in*)addr->ai_addr)->sin_addr, t_payload.destination_ip, sizeof(t_payload.destination_ip));

    freeaddrinfo(addr);
    return (EXIT_SUCCESS);
}

// Init socket and set option

_Bool init_socket()
{   
    // struct timeval timeout = { .tv_sec = 1 };

    t_payload.socket_fd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (t_payload.socket_fd == -1)
        return (ft_perror("Can't create RAW socket\n"));
    if ((setsockopt(t_payload.socket_fd, IPPROTO_IP, IP_TTL, &t_payload.ttl, sizeof(t_payload.ttl))) < 0)
        return (ft_perror("Can't set TTL value\n"));
    // if ((setsockopt(t_payload.socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) < 0)
    //     return (ft_perror("Can't set TIMEOUT\n"));
    return (EXIT_SUCCESS);
}

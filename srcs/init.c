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
    .receive =
    {
        .sin_family = AF_INET,
        .sin_port = 0
    }
};

// Check if destination (host)

_Bool init_destination()
{
    struct addrinfo *addr = NULL;
    struct addrinfo tmp;
    tmp.ai_family = AF_INET;
    tmp.ai_socktype = SOCK_RAW;
    tmp.ai_protocol = IPPROTO_ICMP;

    if (getaddrinfo(t_payload.destination_address, NULL, &tmp, &addr) != EXIT_SUCCESS)
    {
        freeaddrinfo(addr);
        fprintf(stderr, "ft_ping : %s : Name or service not known\n", t_payload.destination_address);
        return (EXIT_FAILURE);
    }
    t_payload.receive.sin_addr.s_addr = ((struct sockaddr_in*)addr->ai_addr)->sin_addr.s_addr;
    // t_payload.addrlen = addr->ai_addrlen;
    // ft_memcpy(&t_payload.receive, addr->ai_addr, sizeof(addr->ai_addr));
    // t_payload.addr2.sin_addr.s_addr = ((struct sockaddr_in*)addr->ai_addr)->sin_addr.s_addr;

    inet_ntop(addr->ai_family, &((struct sockaddr_in*)addr->ai_addr)->sin_addr, t_payload.destination_ip, sizeof(t_payload.destination_ip));

    freeaddrinfo(addr);
    return (EXIT_SUCCESS);
}

// Init socket and set option

_Bool init_socket()
{   
    // struct timeval timeout = { .tv_sec = 1 };

    t_payload.socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (t_payload.socket_fd < 0)
        return (ft_perror("Can't create RAW socket\n"));
    // if ((setsockopt(t_payload.socket_fd, IPPROTO_IP, IP_TTL, &t_payload.ttl, sizeof(t_payload.ttl))) < 0)
        // return (ft_perror("Can't set TTL value\n"));
    // if ((setsockopt(t_payload.socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) < 0)
    //     return (ft_perror("Can't set TIMEOUT\n"));
    return (EXIT_SUCCESS);
}

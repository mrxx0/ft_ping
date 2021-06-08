#include "../includes/ft_ping.h"

_Bool init_host()
{
    struct addrinfo *addr = NULL;
    struct addrinfo tmp;
    tmp.ai_family = PF_INET;
    tmp.ai_socktype = SOCK_RAW;
    tmp.ai_protocol = IPPROTO_ICMP;
    if (getaddrinfo(t_payload.address, NULL, &tmp, &addr))
    {
        free(addr);
        fprintf(stderr, "ft_ping : %s : Name or service not known\n", t_payload.address);
        return (EXIT_FAILURE);
    }
    t_payload.addrlen = addr->ai_addrlen;
    free(addr);
    return (EXIT_SUCCESS);
}

_Bool init_socket()
{
    struct timeval timeout;

    timeout.tv_sec = 1;
    // timeout.tv_usec = 0;

    t_payload.socket_fd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (t_payload.socket_fd == -1)
        return (ft_perror("Can't create RAW socket\n"));
    if ((setsockopt(t_payload.socket_fd, IPPROTO_IP, IP_TTL, &t_payload.ttl, sizeof(t_payload.ttl))) < 0)
        return (ft_perror("Can't set TTL value\n"));
    if ((setsockopt(t_payload.socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) < 0)
        return (ft_perror("Can't set TIMEOUT\n"));
    return (EXIT_SUCCESS);
}
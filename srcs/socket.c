#include "../includes/ft_ping.h"

_Bool init_socket(t_payload *payload)
{
    struct timeval timeout;

    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    payload->socket_fd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (payload->socket_fd == -1)
        return (ft_perror("Can't create RAW socket\n"));
    if ((setsockopt(payload->socket_fd, IPPROTO_IP, IP_TTL, &payload->ttl, sizeof(payload->ttl))) < 0)
        return (ft_perror("Can't set TTL value\n"));
    if ((setsockopt(payload->socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) < 0)
        return (ft_perror("Can't set TIMEOUT\n"));
    return (EXIT_SUCCESS);
}
#include "../includes/ft_ping.h"

_Bool init_socket(t_payload *payload)
{
    payload->socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (payload->socket_fd == -1)
        return (ft_perror("Can't create RAW socket\n"));
    
    return (EXIT_SUCCESS);
}
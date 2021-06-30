#include "../includes/ft_ping.h"

// Init socket and set option

_Bool init_socket()
{   
    int fd = 0;

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (t_payload.socket_fd < 0)
        return (ft_perror("Can't create RAW socket\n"));
    if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, \
		(int[1]){1}, sizeof(int)) == -1)
		  return (ft_perror("Can't set option for socket\n"));
    t_payload.socket_fd = fd;
    return (EXIT_SUCCESS);
}

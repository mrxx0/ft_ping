#include "../includes/ft_ping.h"

_Bool    get_destination(int argc, char **argv)
{
    int i = 1;
    struct addrinfo address_info = {.ai_family = AF_INET, .ai_socktype = SOCK_RAW, .ai_protocol = IPPROTO_ICMP};
    struct addrinfo *tmp  = NULL;
    while (i < argc)
    {
        if (i != t_payload.id_opt)
        {
            ft_memcpy(t_payload.destination_address, argv[i], ft_strlen(argv[i]));
            break ;
        }
        else
            i++;
    }
    if (getaddrinfo(t_payload.destination_address, NULL, &address_info, &tmp))
    {
        fprintf(stderr, "ft_ping : %s : Name or service not known\n", t_payload.destination_address);
        return (EXIT_FAILURE);
    }
    t_payload.receive.sin_addr.s_addr = ((struct sockaddr_in*)tmp->ai_addr)->sin_addr.s_addr;

    inet_ntop(tmp->ai_family, &((struct sockaddr_in*)tmp->ai_addr)->sin_addr, t_payload.destination_ip, sizeof(t_payload.destination_ip));
    if (ft_strcmp(t_payload.destination_ip, t_payload.destination_address) == 0)
        t_payload.display_ip = 0;
    freeaddrinfo(tmp);
    return (EXIT_SUCCESS);
}
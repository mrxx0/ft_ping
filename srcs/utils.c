#include "../includes/ft_ping.h"

void free_addrinfo(struct addrinfo *addr)
{
    struct addrinfo *tmp;

    while (addr != NULL)
    {
        free(addr->ai_canonname);
        tmp = addr;
        addr = addr->ai_next;
        free(tmp);
    }
}
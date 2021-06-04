#include "../includes/ft_ping.h"

t_payload *create_payload(void)
{
    t_payload *payload = NULL;

    payload = malloc(sizeof(t_payload));
    payload->socket_fd = -1;
    payload->address = NULL;
    payload->opt = 0;
    payload->id_opt = 0;
    payload->found_address = 0;
    return (payload);
}
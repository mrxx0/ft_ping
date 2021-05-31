#include "../includes/ft_ping.h"

t_payload *create_payload(void)
{
    t_payload *payload = NULL;

    payload = malloc(sizeof(t_payload));
    return (payload);
}

_Bool    get_destination(int argc, char **argv, int8_t id, t_payload *payload)
{
    (void)argc;
    (void)argv;
    (void)id;
    (void)payload;
    if (argc == 3 && id == 1)
        payload->address = ft_strdup(argv[2]);
    else    
        payload->address = ft_strdup(argv[1]);
    return (EXIT_SUCCESS);
}
#include "../includes/ft_ping.h"

_Bool    get_destination(int argc, char **argv)
{
    int i = 1;

    while (i < argc)
    {
        if (i != t_payload.id_opt)
        {
            ft_memcpy(t_payload.destination_address, argv[i], ft_strlen(argv[i]));
            return (EXIT_SUCCESS);
        }
        else
            i++;
    }
    return (EXIT_SUCCESS);
}
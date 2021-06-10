#include "../includes/ft_ping.h"

_Bool    get_destination(int argc, char **argv)
{
    int i = 1;

    while (i < argc)
    {
        if (i != t_payload.id_opt)
        {
            t_payload.destination_address = ft_strdup(argv[i]);
            if (t_payload.destination_address == MALLOC_FAILED)
                return (ft_perror("Malloc failed\n"));
            return (EXIT_SUCCESS);
        }
        else
            i++;
    }
    return (EXIT_SUCCESS);
}
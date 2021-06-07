#include "../includes/ft_ping.h"

_Bool    get_destination(int argc, char **argv, t_payload *payload)
{
    int i = 1;

    while (i < argc)
    {
        if (i != payload->id_opt && payload->found_address == 0)
        {
            payload->address = ft_strdup(argv[i]);
            if (payload->address == MALLOC_FAILED)
                return (ft_perror("Malloc failed\n"));
            return (EXIT_SUCCESS);
        }
        else
            i++;
    }
    return (EXIT_SUCCESS);
}
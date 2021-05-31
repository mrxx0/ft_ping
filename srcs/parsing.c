#include "../includes/ft_ping.h"

_Bool print_help(void)
{
    printf("Usage: ft_ping [-hv] <destination adress>\n");
    return (EXIT_SUCCESS);
}

_Bool check_for_option(char **argv, int8_t id_opt)
{
    size_t i = 0;

    while (argv[id_opt][i] != '\0')
    {
        if (argv[id_opt][i] == 'v')
        {
            printf("v option parsed\n");
            return (EXIT_SUCCESS);
        }
        else if (argv[id_opt][i] == 'h')
            return (EXIT_FAILURE);
        else
            i++;
    }
    return (EXIT_FAILURE);
}

int8_t find_opt(int argc, char **argv)
{
    int8_t id = -1;
    int i = 1;
    int j = 0;    

    while (i < argc)
    {
        while (argv[i][j] != '\0')
        {
            if (argv[i][j] == '-')
                id = i;
            j++;
        }
        j = 0;
        i++;
    }
    return (id);
}

_Bool parsing_arguments(int argc, char **argv)
{
    int8_t id_opt = 1;
    t_payload *payload = NULL;
    if (argc > 3)
        return (EXIT_FAILURE); 
    else if (argc >= 1)
    {
        if (argc == 3)
        {
            id_opt = find_opt(argc, argv);
            if (id_opt == -1)
                return (EXIT_FAILURE);
            if (check_for_option(argv, id_opt) == EXIT_FAILURE)
                return (EXIT_FAILURE);
        }
        payload = create_payload();
        if (payload == MALLOC_FAILED)
            return (EXIT_FAILURE);
        if (get_destination(argc, argv, id_opt, payload) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        printf("address = [%s]\n", payload->address);
    }
    free(payload->address);
    free(payload);
    return (EXIT_SUCCESS);
}

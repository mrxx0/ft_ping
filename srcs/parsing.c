#include "../includes/ft_ping.h"

_Bool print_help(void)
{
    printf("Usage: ft_ping [-hv] <destination adress>\n");
    return (EXIT_SUCCESS);
}

void parse_opt(char *str, t_payload *payload)
{
    size_t i = 1;

    while (str[i] != '\0')
    {
        if (str[i] == 'h' || str[i] == 'v')
            payload->opt |= str[i] == 'h' ? HELP : VERBOSE;
        else if (str[i] != 'h' && str[i] != 'v')
            payload->opt |= BAD_OPT;
        i++;
    }
    if (payload->opt == 0)
        payload->opt |= NO_OPT;
}

void find_opt(int argc, char **argv, t_payload *payload)
{
    int i = 1;
    int j = 0;
    payload->opt = 0;

    while (i < argc)
    {
        while (argv[i][j] != '\0')
        {
            if (argv[i][j] == '-')
            {
                parse_opt(argv[i], payload);
                payload->id_opt = i;
            }
            j++;
        }
        j = 0;
        i++;
    }
    if (payload->opt == 0)
        payload->opt = NO_OPT;
}

_Bool parsing_arguments(int argc, char **argv)
{
    t_payload *payload = NULL;
    if (argc > 3)
        return (EXIT_FAILURE); 
    else if (argc >= 1)
    {
        payload = create_payload();
        if (payload == MALLOC_FAILED)
            return (EXIT_FAILURE);
        find_opt(argc, argv, payload);

        // if ((payload->opt & HELP) == 1)
        //     printf("HELP\n");
        // if ((payload->opt & VERBOSE) == 2)
        //     printf("VERBOSE\n");
        // if ((payload->opt & BAD_OPT) == 4)
        //     printf("BAD_OPT\n");
        // if ((payload->opt & NO_OPT) == 8)
        //     printf("NO_OPT\n");
            
        if (((payload->opt & BAD_OPT) == 4)
        || ((payload->opt & HELP) == 1)
        || ((argc > 2 && (payload->opt & NO_OPT) == 5)))
        {
            free(payload);
            return (EXIT_FAILURE);
        }
        if (get_destination(argc, argv, payload) == EXIT_FAILURE)
        {
            free(payload);
            return (EXIT_FAILURE);
        }
        printf("address = [%s]\n", payload->address);
    }
    if (payload->address != NULL)
        free(payload->address);
    free(payload);
    return (EXIT_SUCCESS);
}

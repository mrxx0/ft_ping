#include "../includes/ft_ping.h"

_Bool print_help(void)
{
    printf("Usage: ft_ping [-hv] <destination adress>\n");
    return (EXIT_SUCCESS);
}

void parse_opt(char *str)
{
    size_t i = 1;

    while (str[i] != '\0')
    {
        if (str[i] == 'h' || str[i] == 'v')
            t_payload.opt |= str[i] == 'h' ? HELP : VERBOSE;
        else if (str[i] != 'h' && str[i] != 'v')
            t_payload.opt |= BAD_OPT;
        i++;
    }
    if (t_payload.opt == 0)
        t_payload.opt |= NO_OPT;
}

void find_opt(int argc, char **argv)
{
    int i = 1;
    int j = 0;
    t_payload.opt = 0;

    while (i < argc)
    {
        while (argv[i][j] != '\0')
        {
            if (argv[i][j] == '-')
            {
                parse_opt(argv[i]);
                t_payload.id_opt = i;
            }
            j++;
        }
        j = 0;
        i++;
    }
    if (t_payload.opt == 0)
        t_payload.opt = NO_OPT;
}

_Bool parsing_arguments(int argc, char **argv)
{
    if (argc > 3)
        return (EXIT_FAILURE); 
    else if (argc >= 1)
    {        

        find_opt(argc, argv);

        // if ((t_payload.opt & HELP) == 1)
        //     printf("HELP\n");
        // if ((t_payload.opt & VERBOSE) == 2)
        //     printf("VERBOSE\n");
        // if ((t_payload.opt & BAD_OPT) == 4)
        //     printf("BAD_OPT\n");
        // if ((t_payload.opt & NO_OPT) == 8)
        //     printf("NO_OPT\n");
            
        if (((t_payload.opt & BAD_OPT) == 4)
        || ((t_payload.opt & HELP) == 1)
        || ((argc > 2 && (t_payload.opt & NO_OPT) == 5)))
        {
            return (EXIT_FAILURE);
        }
        if (get_destination(argc, argv) == EXIT_FAILURE)
        {
            printf("Error get_destination\n");
            // free(payload);
            return (EXIT_FAILURE);
        }
       
    }
    // if (t_payload.address != NULL)
    //     free(t_payload.address);
    // free(payload);
    return (EXIT_SUCCESS);
}

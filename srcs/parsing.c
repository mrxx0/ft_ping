#include "../includes/ft_ping.h"

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
        if (((t_payload.opt & BAD_OPT) == 4)
        || ((t_payload.opt & HELP) == 1)
        || ((argc > 2 && (t_payload.opt & NO_OPT) == 5)))
        {
            return (EXIT_FAILURE);
        }
        if (get_destination(argc, argv) == EXIT_FAILURE)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

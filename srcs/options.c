#include "../includes/ft_ping.h"

_Bool print_help(void)
{
    printf("Usage: ft_ping [-hv] <destination adress>\n");
    return (EXIT_SUCCESS);
}

_Bool check_for_option(char **argv)
{
    size_t i = 1;

    while (argv[1][i] != '\0')
    {
        if (argv[1][i] == 'v')
            printf("v option parsed\n");
        else if (argv[1][i] == 'h')
            return (print_help());
        else
            return (EXIT_FAILURE);
        i++;
    }
    return (EXIT_SUCCESS);
}
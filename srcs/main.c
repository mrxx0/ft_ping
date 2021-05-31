#include "../includes/ft_ping.h"

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (argv[1][0] == '-')
        {
            if (check_for_option(argv) == EXIT_FAILURE)
                return (EXIT_FAILURE);
        }
    }
    else
        print_help();
	return (EXIT_SUCCESS);
}
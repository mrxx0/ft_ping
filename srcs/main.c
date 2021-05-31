#include "../includes/ft_ping.h"

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (parsing_arguments(argc, argv) == EXIT_FAILURE)
        {
            print_help();
            return (EXIT_FAILURE);
        }
    }
    else
        print_help();
	return (EXIT_SUCCESS);
}
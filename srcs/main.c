#include "../includes/ft_ping.h"

int main(int argc, char **argv)
{
    if (getuid() != 0)
    {
        write(2, "ft_ping : You need to be root.\n", ft_strlen("ft_ping : You need to be root.\n"));
        return (EXIT_FAILURE);
    }
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
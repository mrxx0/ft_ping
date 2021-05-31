#include "../includes/ft_ping.h"

int main(int argc, char **argv)
{
    // t_payload   *payload = NULL;
    // _Bool       shift = 0;
    if (argc > 1)
    {
        if (parsing_arguments(argc, argv) == EXIT_FAILURE)
        {
            print_help();
            return (EXIT_FAILURE);
        }
        // if (argv[1][0] == '-')
        // {
        //     if (check_for_option(argv) == EXIT_FAILURE)
        //         return (EXIT_FAILURE);
        //     shift = 1;
        //     get_destination(argv, *payload, shift);

        // }
        // else if (argc == 2)
        //     get_destination(argv, *payload, shift);
        // else
        //     return (EXIT_FAILURE);
    }
    else
        print_help();
	return (EXIT_SUCCESS);
}
#include "../includes/ft_ping.h"

int main(int argc, char **argv)
{
    t_payload *payload = create_payload();

    if (payload == MALLOC_FAILED)
        return (EXIT_FAILURE);
    if (getuid() != 0)
    {
        write(2, "ft_ping : You need to be root.\n", ft_strlen("ft_ping : You need to be root.\n"));
        return (EXIT_FAILURE);
    }
    if (argc > 1)
    {
        if (parsing_arguments(argc, argv, payload) == EXIT_FAILURE)
        {
            free(payload->address);
            free(payload);
            print_help();
            return (EXIT_FAILURE);
        }
        if (init_socket(payload) == EXIT_FAILURE)
        {
            free(payload->address);
            free(payload);
            return (EXIT_FAILURE);
        }
        free(payload->address);
        free(payload);
    }
    else
        print_help();
	return (EXIT_SUCCESS);
}
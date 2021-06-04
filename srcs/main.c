#include "../includes/ft_ping.h"

int main(int argc, char **argv)
{
    t_payload *payload = NULL;
    // if (getuid() != 0)
    // {
    //     write(2, "ft_ping : You need to be root.\n", ft_strlen("ft_ping : You need to be root.\n"));
    //     return (EXIT_FAILURE);
    // }
    if (argc > 1)
    {
        if (parsing_arguments(argc, argv, payload) == EXIT_FAILURE)
        {
            print_help();
            return (EXIT_FAILURE);
        }
        printf("payload socket = %d\n", payload->socket_fd);
        printf("payload opt = %d\n", payload->opt);
        printf("payload id_opt = %d\n", payload->socket_fd);
        printf("payload found_address = %d\n", payload->found_address);
        printf("payload address = %s\n", payload->address);

        if (init_socket(payload) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        free(payload->address);
        free(payload);
    }
    else
        print_help();
	return (EXIT_SUCCESS);
}
#include "../includes/ft_ping.h"


struct s_payload t_payload = {
    .socket_fd = 0,
    .ttl = 0,
    .opt = 0,
    .id_opt = 0,
    .address = NULL
};

void print_payload()
{
    printf("socket_fd = [%d]\n", t_payload.socket_fd);
    printf("ttl = [%d]\n", t_payload.ttl);
    printf("opt = [%d]\n", t_payload.opt);
    printf("id_opt = [%d]\n", t_payload.id_opt);
    printf("address = [%s]\n", t_payload.address);
}

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
            // free(t_payload.address);
            // free(payload);
            print_help();
            return (EXIT_FAILURE);
        }
                print_payload();

        if (init_socket() == EXIT_FAILURE)
        {
            // free(t_payload.address);
            // free(payload);
            return (EXIT_FAILURE);
        }
        if (init_host() == EXIT_FAILURE)
        {
            // free(t_payload.address);
            // free(payload);
            return (EXIT_FAILURE);
        }
        // free(&t_payload.addrlen);
        // free(t_payload.address);
        // free(payload);
    }
    else
        print_help();
	return (EXIT_SUCCESS);
}
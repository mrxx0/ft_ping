#include "../includes/ft_ping.h"

struct s_payload t_payload = {
    .socket_fd = 0,
    .ttl = 64,
    .seq = 0,
    .opt = 0,
    .id_opt = 0,
    .timeout = 1,
    .destination_address = {0},
    .destination_ip = {0},
    .receive =
    {
        .sin_family = AF_INET,
        .sin_port = 0
    }
};

void print_payload()
{
    printf("socket_fd = [%d]\n", t_payload.socket_fd);
    printf("ttl = [%d]\n", t_payload.ttl);
    printf("opt = [%d]\n", t_payload.opt);
    printf("id_opt = [%d]\n", t_payload.id_opt);
    printf("address = [%s]\n", t_payload.destination_address);
    printf("ip = [%s]\n", t_payload.destination_ip);
}

int main(int argc, char **argv)
{    
    if (getuid() != VALID_ROOT_UID)
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
       
        if (init_socket() == EXIT_FAILURE)
            return (EXIT_FAILURE);
        // if (init_destination() == EXIT_FAILURE)
        //     return (EXIT_FAILURE);
        print_payload();

        loop();
    }
    else
        print_help();
	return (EXIT_SUCCESS);
}
#include "../includes/ft_ping.h"

void print_payload(t_payload *payload)
{
    printf("socket_fd = [%d]\n", payload->socket_fd);
    printf("ttl = [%d]\n", payload->ttl);
    printf("opt = [%d]\n", payload->opt);
    printf("id_opt = [%d]\n", payload->id_opt);
    printf("address = [%s]\n", payload->address);
    printf("found_address = [%d]\n", payload->found_address);
}

int main(int argc, char **argv)
{
    t_payload *payload = NULL;
    
    if (getuid() != 0)
    {
        write(2, "ft_ping : You need to be root.\n", ft_strlen("ft_ping : You need to be root.\n"));
        return (EXIT_FAILURE);
    }
    if (argc > 1)
    {
        payload = create_payload();
        if (payload == MALLOC_FAILED)
            return (EXIT_FAILURE);
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
        if (init_host(payload) == EXIT_FAILURE)
        {
            free(payload->address);
            free(payload);
            return (EXIT_FAILURE);
        }
        print_payload(payload);
        free(payload->address);
        free(payload);
    }
    else
        print_help();
	return (EXIT_SUCCESS);
}
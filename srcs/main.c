#include "../includes/ft_ping.h"

struct s_payload t_payload = {
    .socket_fd = 0,
    .ttl = 64,
    .seq = 0,
    .rec = 0,
    .opt = 0,
    .id_opt = 0,
    .destination_address = {0},
    .display_ip = 1,
    .destination_ip = {0},
    .receive =
    {
        .sin_family = AF_INET,
        .sin_port = 0
    },
    .rtt_min = 0,
    .rtt_max = 0,
    .rtt_avg = 0,
    .rtt_mul = 0,
    .start_time = 0
};

int main(int argc, char **argv)
{    
    if (getuid() != VALID_ROOT_UID)
    {
        write(2, "ft_ping : You need to be root.\n", ft_strlen("ft_ping : You need to be root.\n"));
        return (EXIT_FAILURE);
    }
    if (argc > 1)
    {
        if (signal(SIGALRM, &send_request) == SIG_ERR
            || signal(SIGINT, &close_ping) == SIG_ERR)
            ft_perror("Alarm failed\n");
        if (parsing_arguments(argc, argv) == EXIT_FAILURE)
        {
            if (((t_payload.opt & HELP) == 1
            || (t_payload.opt & VERBOSE) == 2
            || (t_payload.opt & BAD_OPT) == 4)
            && !t_payload.destination_address[0])
                print_help();
            return (EXIT_FAILURE);
        }
        if (init_socket() == EXIT_FAILURE)
            return (EXIT_FAILURE);
        if ((t_payload.opt & VERBOSE) == 2)
            print_info();
        loop();
    }
    else
        print_help();
	return (EXIT_SUCCESS);
}
#include "../includes/ft_ping.h"

void print_info()
{
	printf("socket_fd = [%d]\n", t_payload.socket_fd);
    printf("ttl = [%d]\n", t_payload.ttl);
    printf("opt = [%d]\n", t_payload.opt);
    printf("id_opt = [%d]\n", t_payload.id_opt);
    printf("address = [%s]\n", t_payload.destination_address);
    printf("ip = [%s]\n", t_payload.destination_ip);
}

void close_ping()
{
    close(t_payload.socket_fd);
	float loss = (1.0f - t_payload.rec / (float)t_payload.seq) * 100.0f;

	printf("\n--- %s ping statistics ---\n", t_payload.destination_address);
	printf("%d packets transmitted, %d received, %d%% packet loss, time Xms\n", t_payload.seq, t_payload.rec, (int)loss);
	printf("rtt min/avg/max/mdev = X/X/X/X ms");
    exit(EXIT_SUCCESS);
}

uint16_t checksum(void *to_check, size_t size)
{
    unsigned short *buf = to_check;
	unsigned int tmp = 0;
	unsigned short result;

	while (size > 1)
	{
		tmp += *buf++;
		size = size -2;
	}
	if ( size == 1 )
		tmp += *(unsigned char*)buf;
	tmp = (tmp >> 16) + (tmp & 0xFFFF);
	tmp += (tmp >> 16);
	result = ~tmp;
	return (result);
}
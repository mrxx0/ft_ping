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
    printf("ft_ping stopped by user.\n%d ping sent to %s at %s\n", t_payload.seq, t_payload.destination_address, t_payload.destination_ip);
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
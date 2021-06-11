#include "../includes/ft_ping.h"

void fill_data(char *ptr, char tmp[ICMP_HEADER_SIZE + ICMP_PACKET_SIZE])
{
	char fill = 0x42;
	while (ptr != (tmp + t_payload.data_size))
	{
		*ptr = fill;
		ptr++;
		fill++;
	}
}

void send_request()
{
    size_t  bytes_sent;
    char    tmp[ICMP_HEADER_SIZE + ICMP_PACKET_SIZE];
    char    *ptr = tmp + ICMP_HEADER_SIZE;
    struct icmphdr *icmp = (struct icmphdr*)tmp;
    (void)bytes_sent;
    (void)ptr;

    init_icmp(icmp);
    printf("\n\nicmp->type = %d\n", icmp->type);
    printf("icmp->code = %d\n", icmp->code);
    printf("icmp->checksum = %d\n", icmp->checksum);
    printf("icmp->un.echo.id = %d\n", icmp->un.echo.id);

    fill_data(ptr, tmp);
}

void loop()
{
    send_request();
    printf("ft_ping (%s) %s\n", t_payload.destination_address, t_payload.destination_address);
}

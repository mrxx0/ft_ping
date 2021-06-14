#include "../includes/ft_ping.h"

void send_request()
{
    size_t  bytes_sent;
    char    tmp[t_payload.data_size];
    // char    *ptr = tmp + ICMP_HEADER_SIZE;
    struct icmphdr *icmp = (struct icmphdr*)tmp;
    (void)bytes_sent;

    init_icmp(icmp);
    printf("\n\nicmp->type = %d\n", icmp->type);
    printf("icmp->code = %d\n", icmp->code);
    printf("icmp->checksum = %d\n", icmp->checksum);
    printf("icmp->un.echo.id = %d\n", icmp->un.echo.id);

    /* 
    Need to fill the ICMP packet with random data
    */
    icmp->checksum = checksum(icmp, t_payload.data_size);
    printf("%u\n", icmp->checksum);
    bytes_sent = sendto(t_payload.socket_fd, icmp, t_payload.data_size, 0, &t_payload.addr, t_payload.addrlen);
    printf("%zu\n", bytes_sent);
}

void loop()
{
    send_request();
    printf("ft_ping (%s) %s\n", t_payload.destination_address, t_payload.destination_address);
}

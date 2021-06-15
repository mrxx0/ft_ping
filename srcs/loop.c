#include "../includes/ft_ping.h"

_Bool receive_response()
{
    char                receive_tmp[128];
    int                 receive_flag = 0;
    ssize_t             receive_bytes;
    struct sockaddr     receive_dst;
    struct iovec        receive_iov;
    struct msghdr       receive_msg;
    // struct iphdr     *receive_ip = (struct iphdr *) receive_tmp;
    struct icmphdr      *receive_icmp = (struct icmphdr *) (receive_tmp + IP_HEADER_SIZE);

    receive_iov.iov_base = receive_tmp;
    receive_iov.iov_len = sizeof(receive_tmp);
    receive_msg.msg_name = (void*)&receive_dst;
    receive_msg.msg_namelen = sizeof(receive_dst);
    receive_msg.msg_iov = &receive_iov;
    receive_msg.msg_iovlen = 1;

    while (42)
    {
        receive_bytes = recvmsg(t_payload.socket_fd, &receive_msg, receive_flag);
        receive_flag = MSG_DONTWAIT;

        if (receive_bytes < 0) // Socket marked nonblocking
        {
            printf("TIMEOUT -> %zd\n", receive_bytes);
            return (EXIT_FAILURE);
        }
        if (receive_icmp->un.echo.id != getpid())
        {
            receive_flag = 0;
        }
        else if (receive_icmp->type != ICMP_ECHOREPLY)
        {
            printf("This is not an echo reply\n");
            return (EXIT_FAILURE);
        }
        printf("RECEIVE [%zu bytes ]OK\n", receive_bytes);
    }
    return (EXIT_SUCCESS);
}

void send_request()
{
    size_t  send_bytes;
    char    send_tmp[ICMP_SIZE];
    // char    *ptr = tmp + ICMP_HEADER_SIZE;
    struct icmphdr *send_icmp = (struct icmphdr*)send_tmp;

    init_icmp(send_icmp);
    printf("\n\nicmp->type = %d\n", send_icmp->type);
    printf("icmp->code = %d\n", send_icmp->code);
    printf("icmp->checksum = %d\n", send_icmp->checksum);
    printf("icmp->un.echo.id = %d\n", send_icmp->un.echo.id);

    /* 
    Need to fill the ICMP packet with random data
    */
    send_icmp->checksum = checksum(send_icmp, ICMP_SIZE);
    printf("%u\n", send_icmp->checksum);
    send_bytes = sendto(t_payload.socket_fd, send_icmp, ICMP_SIZE, 0, &t_payload.addr, t_payload.addrlen);
    printf("%zu\n", send_bytes);
}

void loop()
{
    printf("ft_ping %s (%s) %lu(%lu) bytes of data.\n", t_payload.destination_address, t_payload.destination_ip, ICMP_SIZE - ICMP_HEADER_SIZE, ICMP_SIZE);
    while (1)
    {
        send_request();
        if (receive_response() == EXIT_FAILURE)
            printf("RECEIVE KO\n");
            //wait_to_receive();
    }
}

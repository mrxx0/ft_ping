#include "../includes/ft_ping.h"

_Bool receive_response(struct sockaddr_in sockaddr)
{
    // char                receive_tmp[128];
    char                packet[ICMP_SIZE + IP_HEADER_SIZE];
    ssize_t             receive_bytes;
    // struct iovec        receive_iov =
    // {
    //     .iov_base = packet,
    //     .iov_len = ICMP_SIZE + IP_HEADER_SIZE
    // };
    struct iovec        receive_iov =
    {
        .iov_base = packet,
        .iov_len = sizeof(packet)
    };
    struct msghdr       receive_msg = 
    {
        .msg_name = &sockaddr,
        .msg_namelen = sizeof(sockaddr),
        .msg_iov = &receive_iov,
        .msg_iovlen = 1,
        .msg_control = packet,
        .msg_controllen = sizeof(packet),
        .msg_flags = 0
    };
    printf("receiving...\n");
    receive_bytes = recvmsg(t_payload.socket_fd, &receive_msg, 0);
    printf("receive_byte = %zd\n", receive_bytes);
    return (EXIT_SUCCESS);
}

void send_request()
{
    ssize_t  send_bytes;
    char    send_tmp[ICMP_SIZE + IP_HEADER_SIZE];

    t_payload.seq++;
    init_ip(send_tmp);
    init_icmp(send_tmp + IP_HEADER_SIZE);
    send_bytes = sendto(t_payload.socket_fd, send_tmp, ICMP_SIZE + IP_HEADER_SIZE, 0, (const struct sockaddr *)&t_payload.receive, t_payload.addrlen);
    printf("send ok with %zd bytes\n", send_bytes);
    
}

void loop()
{
    printf("ft_ping %s (%s) %lu(%lu) bytes of data.\n", t_payload.destination_address, t_payload.destination_ip, ICMP_SIZE - ICMP_HEADER_SIZE, ICMP_SIZE + IP_HEADER_SIZE);
    while (1)
    {
        send_request();
        receive_response(t_payload.receive);
        // if (receive_response() == EXIT_FAILURE)
        //     printf("RECEIVE KO\n");
        //     //wait_to_receive();
    }
}

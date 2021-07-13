#include "../includes/ft_ping.h"

// Loop till the user stop with ctrl + C by sending and receiving echo reply/response

ssize_t receive_echo_response(int socket, struct sockaddr_in sockaddr, void *packet)
{
    char    tmp[512];
    ssize_t receive_bytes = 0;
    struct iovec io = 
    {
        .iov_base = packet,
        .iov_len = 84
    };
    struct msghdr msg = 
    {
        .msg_name = &sockaddr,
        .msg_namelen = sizeof(sockaddr),
        .msg_iov = &io,
        .msg_iovlen = 1,
        .msg_control = tmp,
        .msg_controllen = sizeof(tmp),
        .msg_flags = 0
    };
    receive_bytes = recvmsg(socket, &msg, 0);
    if (receive_bytes == -1)
        return (EXIT_FAILURE);
    return (receive_bytes);
}

_Bool receive_response()
{
    char    receive_packet[84];

    while (1)
    {
        if (receive_echo_response(t_payload.socket_fd, t_payload.receive, receive_packet) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        t_payload.seq++;
        check_response(receive_packet);
    }

    return (EXIT_SUCCESS);
}

void send_echo_request(int socket, const struct sockaddr *dst, char *packet)
{
    ssize_t bytes_sent;

    bytes_sent = sendto(socket, packet, IP_HEADER_SIZE + ICMP_SIZE, 0, dst, sizeof(*dst));
    if (bytes_sent == -1)
    {
        printf("Error send echo request\n");
        return ;
    }


}
void send_request()
{
    char    packet_sent[ICMP_SIZE + IP_HEADER_SIZE];

    if (t_payload.start_time == 0)
        t_payload.start_time = start_time();

    init_ip(packet_sent, t_payload.receive.sin_addr.s_addr);
    init_icmp(packet_sent + IP_HEADER_SIZE);
    send_echo_request(t_payload.socket_fd, (const struct sockaddr *)&t_payload.receive, packet_sent);
    alarm(1);
}

void loop()
{
    printf("PING %s (%s) %lu(%lu) bytes of data.\n", t_payload.destination_address, t_payload.destination_ip, ICMP_SIZE - ICMP_HEADER_SIZE, ICMP_SIZE + IP_HEADER_SIZE);
    while (1)
    {
        send_request();    
        if (receive_response() == EXIT_FAILURE)
            printf("RECEIVE KO\n");
    }
}

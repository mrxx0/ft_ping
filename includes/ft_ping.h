#ifndef FT_PING_H
#define FT_PING_H

#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/icmp.h>
#include <linux/ip.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

#define VALID_ROOT_UID 0

# define HELP	    1
# define VERBOSE	2
# define BAD_OPT    4
# define NO_OPT     8 

# define ICMP_PACKET_SIZE 56
# define ICMP_HEADER_SIZE sizeof(struct icmphdr)
# define ICMP_SIZE ICMP_PACKET_SIZE + ICMP_HEADER_SIZE
# define IP_HEADER_SIZE sizeof(struct iphdr)

// ICMP_PACKET_SIZE = 56
// ICMP_HEADER_SIZE = 8
// ICMP_SIZE = 64
// IP_HEADER_SIZE = 20

extern struct  s_payload
{
    int                 socket_fd;
    int                 ttl;
    int                 opt;
    int                 id_opt;
    u_int16_t           seq;
    u_int16_t           rec;
    _Bool               display_ip;
    _Bool               display_rtt;
    char                destination_address[NI_MAXHOST]; // maximum domain name based on arpa/nameser.h
    char                destination_ip[INET_ADDRSTRLEN]; // maximum IP len
    char                pad[1];
    socklen_t           addrlen;
    struct sockaddr_in  receive;
    char                pad_2[4];
    suseconds_t         rtt_min;
    suseconds_t         rtt_max;
    suseconds_t         rtt_avg;
    suseconds_t         rtt_mul;
    suseconds_t         start_time;
}               t_payload;

/*  FT_PING   */

_Bool       parsing_arguments(int argc, char **argv);
_Bool       check_for_option(char **argv, int8_t id_opt);
_Bool       print_help(void);
_Bool       get_destination(int argc, char **argv);
_Bool       init_socket();
_Bool       init_destination();
void        init_ip (void *ip, u_int32_t dst);
void        init_icmp(void *icmp);
void        loop();
void        send_request();
suseconds_t get_rtt(struct timeval *time);
void        check_response(void *receive_packet);
suseconds_t get_time (void);
suseconds_t start_time(void);

/*  LIBFT   */

char	    *ft_strdup(const char *s1);
size_t	    ft_strlen(const char *s);
_Bool       ft_isdigit(char c);
_Bool       ft_perror(char *error);
void        *ft_memcpy(void *dst, const void *src, size_t size);
int		    ft_strcmp(const char *s1, const char *s2);

/*  UTILS   */

uint16_t    checksum(void *to_check, size_t size);
void        close_ping();
void        print_info();



uint16_t    swap16(uint16_t nb);

#endif 

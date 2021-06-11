#ifndef FT_PING_H
#define FT_PING_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <netdb.h>

#define MALLOC_FAILED NULL

#define VALID_ROOT_UID 0

# define HELP	    1
# define VERBOSE	2
# define BAD_OPT    4
# define NO_OPT     8 

# define ICMP_PACKET_SIZE 56
# define ICMP_HEADER_SIZE sizeof(struct icmphdr)

extern struct  s_payload
{
    int             socket_fd;
    int             ttl;
    int             opt;
    int             id_opt;
    int             data_size;
    char            pad[4];
    long            timeout;
    char            destination_address[NI_MAXHOST]; // maximum domain name based on arpa/nameser.h
    char            pad_2[7];
    char            destination_ip[INET_ADDRSTRLEN]; // maximum IP len
    socklen_t       addrlen;
    struct sockaddr addr;
    char            pad_3[4];

}               t_payload;

/*  FT_PING   */

_Bool       parsing_arguments(int argc, char **argv);
_Bool       check_for_option(char **argv, int8_t id_opt);
_Bool       print_help(void);
_Bool       get_destination(int argc, char **argv);
_Bool       init_socket();
_Bool       init_destination();
void        loop();

/*  LIBFT   */

char	    *ft_strdup(const char *s1);
size_t	    ft_strlen(const char *s);
_Bool       ft_isdigit(char c);
_Bool       ft_perror(char *error);
void        *ft_memcpy(void *dst, const void *src, size_t size);

/*  UTILS   */

void free_addrinfo(struct addrinfo *addr);

#endif 

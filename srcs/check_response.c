#include "../includes/ft_ping.h"

static const char *error_id[] = {
    "Echo Reply",
    "None",
    "None",
    "Dest unreachable",
    "Packet lost, slow down",
    "Shorter route",
    "None",
    "None",
    "Echo service",
    "Router advertisement",
    "Router solicitation",
    "Time to live exceeded",
    "IP header bad",
    "Timestamp request",
    "Timestamp reply",
    "Information request",
    "Information reply",
    "Address mask request",
    "Address mask reply"
};

static const char *error_details[] = {
    "(Bad net)",
    "(Bad host)",
    "(Bad protocol)",
    "(Bad port)",
    "(IP_DF cause drop)",
    "(Src routee failed)",
    "(Unknow net)",
    "(Unknow host)",
    "(Src host isolated)",
    "(Net denied)",
    "(Host denied)",
    "(Bad tos for net)",
    "(Bad tos for host)",
    "(Admin prohib)",
    "(Host prec vio.)",
    "(Prec cutoff)"
};

// Check the validity of the echo response

void check_response(void *receive_packet)
{
    struct iphdr    *ip = receive_packet;
    struct icmphdr  *icmp = receive_packet + IP_HEADER_SIZE;
    suseconds_t     rtt;
    // printf("id = %d | pid = %d\n", icmp->un.echo.id, swap16((uint16_t)getpid()));
    if (icmp->un.echo.id == swap16((uint16_t)getpid()))
    {
        if (icmp->type != ICMP_ECHOREPLY)
        {
            t_payload.display_rtt = FALSE;
            if ((t_payload.opt & VERBOSE) == 2)
            {
                if (t_payload.display_ip == 1)
                    printf("%lu bytes from %s (%s): icmp_seq=%hu %s %s\n", (uint16_t)(ntohs(ip->tot_len)) - IP_HEADER_SIZE, t_payload.destination_address, t_payload.destination_ip, t_payload.seq, error_id[icmp->type], error_details[icmp->code]);
                else
                    printf("%lu bytes from %s: icmp_seq=%hu %s %s\n", (uint16_t)(ntohs(ip->tot_len)) - IP_HEADER_SIZE, t_payload.destination_address, t_payload.seq, error_id[icmp->type], error_details[icmp->code]);
            }
            else
           {
               if (t_payload.display_ip == 1)
                   printf("%lu bytes from %s (%s): icmp_seq=%hu %s\n", (uint16_t)(ntohs(ip->tot_len)) - IP_HEADER_SIZE, t_payload.destination_address, t_payload.destination_ip, t_payload.seq, error_id[icmp->type]);
               else
                  printf("%lu bytes from %s: icmp_seq=%hu %s\n", (uint16_t)(ntohs(ip->tot_len)) - IP_HEADER_SIZE, t_payload.destination_address, t_payload.seq, error_id[icmp->type]);
            }  
        }
        else
        {   
            rtt = get_rtt(receive_packet + IP_HEADER_SIZE + ICMP_HEADER_SIZE + 4);
            if (t_payload.display_ip == 1)
                printf("%lu bytes from %s (%s): icmp_seq=%hu ttl=%hhu time=%ld.%.1ld ms\n", (uint16_t)(ntohs(ip->tot_len)) - IP_HEADER_SIZE, t_payload.destination_address, t_payload.destination_ip, t_payload.seq, ip->ttl, rtt / 1000, rtt % 1000);
            else
                printf("%lu bytes from %s: icmp_seq=%hu ttl=%hhu time=%ld.%.1ld ms\n", (uint16_t)(ntohs(ip->tot_len)) - IP_HEADER_SIZE, t_payload.destination_address, t_payload.seq, ip->ttl, rtt / 1000, rtt % 1000);
        }
        // t_payload.seq++;
        t_payload.rec++;

    }
    else
        printf("id response is : %d | PID is : %d\n", icmp->un.echo.id, swap16((uint16_t)getpid()));
}
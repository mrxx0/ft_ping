#include "../includes/ft_ping.h"

suseconds_t start_time(void)
{
     struct timeval	actual_time;

	if (gettimeofday(&actual_time, NULL) == -1)
	{
        ft_perror("Can't get time of the day\n");
		return (0);
	}
    return (t_payload.start_time = actual_time.tv_sec * 1000000 + actual_time.tv_usec);
}

// Get the RTT value with min/max/avg and start time of the command

suseconds_t get_time (void)
{
    struct timeval	actual_time;

	if (gettimeofday(&actual_time, NULL) == -1)
	{
        ft_perror("Can't get time of the day\n");
		return (0);
	}
    if (t_payload.seq == 1)
        t_payload.start_time = actual_time.tv_sec * 1000000 + actual_time.tv_usec;
	return (actual_time.tv_sec * 1000000 + actual_time.tv_usec);
}

suseconds_t get_rtt(struct timeval *time)
{
    suseconds_t     actual_time = get_time();
    suseconds_t     rtt = actual_time - time->tv_sec * 1000000 - time->tv_usec;
    
    if (t_payload.seq == 1)
    {
        t_payload.rtt_min = rtt;
        t_payload.rtt_max = rtt;
        t_payload.rtt_avg = rtt;
        t_payload.rtt_mul = rtt * rtt;
    }
    else
    {
        t_payload.rtt_min = t_payload.rtt_min > rtt ? rtt : t_payload.rtt_min;
        t_payload.rtt_max = t_payload.rtt_max < rtt ? rtt : t_payload.rtt_max;
        t_payload.rtt_avg = t_payload.rtt_avg + rtt;
        t_payload.rtt_mul = t_payload.rtt_mul + (rtt * rtt);
    }
    return (rtt);
}

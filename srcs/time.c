#include "../includes/ft_ping.h"

suseconds_t get_time (void)
{
    struct timeval	actual_time;

	if (gettimeofday(&actual_time, NULL) == -1)
	{
        ft_perror("Can't get time of the day\n");
		return (0);
	}
	return (actual_time.tv_sec * 1000000 + actual_time.tv_usec);
}

suseconds_t get_rtt(struct timeval *time)
{
    suseconds_t     actual_time = get_time();
    // printf("actual time = %ld\n", actual_time);
    // printf("time->tv_sec = %ld\n", time->tv_sec);
    // printf("time->tv_usec = %ld\n", time->tv_usec);
    suseconds_t     rtt = actual_time - time->tv_sec * 1000000 - time->tv_usec;

    return (rtt);
}

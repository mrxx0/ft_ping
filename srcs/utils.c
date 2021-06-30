#include "../includes/ft_ping.h"

_Bool print_help(void)
{
    printf("Usage: \tft_ping [-v] <destination adress>\n\tft_ping -h\n");
    return (EXIT_SUCCESS);
}

void print_info()
{
	printf("______________________________________________\n");
	printf("\t\tVERBOSE MODE\n\n");
	printf("Reading socket on fd = [%d]\n", t_payload.socket_fd);
    printf("TTL value = [%d]\n", t_payload.ttl);
    printf("opt = [%d]\n", t_payload.opt);
    printf("Option found at id = [%d]\n", t_payload.id_opt);
    printf("Destination address  = [%s]\n", t_payload.destination_address);
    printf("Destination ip = [%s]\n", t_payload.destination_ip);
	printf("______________________________________________\n");

}

void close_ping()
{
    close(t_payload.socket_fd);
	float loss = (1.0f - t_payload.rec / (float)t_payload.seq) * 100.0;
	suseconds_t time_diff = get_time() - t_payload.start_time;

	printf("\n--- %s ping statistics ---\n", t_payload.destination_address);
	printf("%d packets transmitted, %d received, %d%% packet loss, time %ldms\n",
		t_payload.seq,
		t_payload.rec,
		(int)loss,
		time_diff / 1000);
	if (t_payload.rec > 0)
    {
        suseconds_t mdev;

        mdev = t_payload.rtt_avg / t_payload.rec;
		t_payload.rtt_mul = t_payload.rtt_mul / t_payload.rec;
		mdev = sqrtl(t_payload.rtt_mul - mdev * mdev);

		printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
		t_payload.rtt_min / 1000.0,
		(t_payload.rtt_avg / (float)t_payload.rec) / 1000.0,
		t_payload.rtt_max / 1000.0,
		mdev / 1000.0);
    }
    exit(EXIT_SUCCESS);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

uint16_t checksum(void *to_check, size_t size)
{
    unsigned short *buf = to_check;
	unsigned int tmp = 0;
	unsigned short result;

	while (size > 1)
	{
		tmp += *buf++;
		size = size -2;
	}
	if ( size == 1 )
		tmp += *(unsigned char*)buf;
	tmp = (tmp >> 16) + (tmp & 0xFFFF);
	tmp += (tmp >> 16);
	result = ~tmp;
	return (result);
}
#include "../includes/ft_ping.h"

/**/

uint16_t    swap16(uint16_t nb)
{
    return ((nb << 8) | (nb >> 8));
}

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;
	char	*b_cpy;

	b_cpy = (char *)b;
	i = 0;
	while (i < n)
	{
		b_cpy[i] = (unsigned char)c;
		i++;
	}
	return (b_cpy);
}
void *ft_memcpy(void *dst, const void *src, size_t size)
{
	size_t i = 0;

	while (i < size)
	{
		((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	return (dst);
}

_Bool ft_perror(char *error)
{
    write(2, error, ft_strlen(error));
    return (EXIT_FAILURE);
}

_Bool ft_isdigit(char c)
{
	if (c > 57 && c < 48)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

size_t	ft_strlen(const char *s)
{
	int count;

	if (s)
	{
		count = 0;
		while (s[count])
			count++;
		return (count);
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(s1);
	dest = NULL;
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

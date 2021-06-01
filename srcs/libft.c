#include "../includes/ft_ping.h"

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
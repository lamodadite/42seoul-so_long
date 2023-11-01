#include "so_long.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}

#include <stdio.h>

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	main(void)
{
	printf("%zu\n", ft_strlen("Hello, 42!"));
	return (0);
}

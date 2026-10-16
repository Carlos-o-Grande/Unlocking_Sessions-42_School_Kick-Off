#include <stdio.h>
#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = b;
	while (len--)
		*p++ = (unsigned char)c;
	return (b);
}

int	main(void)
{
	int	x;
	int	y;
	int	arr[5];

	printf("%d\n", x);
	y = 0;
	printf("%d\n", y);
	ft_memset(arr, 0, sizeof(arr));
	printf("%d %d\n", arr[0], arr[4]);
	return (0);
}

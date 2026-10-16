#include <stdio.h>

int	main(void)
{
	int		arr[5];
	size_t	len;
	int		*ptr;

	arr[0] = 10;
	arr[1] = 20;
	arr[2] = 30;
	arr[3] = 40;
	arr[4] = 50;
	len = sizeof(arr) / sizeof(arr[0]);
	ptr = arr;
	while (ptr < arr + len)
	{
		printf("%d\n", *ptr);
		ptr++;
	}
	return (0);
}

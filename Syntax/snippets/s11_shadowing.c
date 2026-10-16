#include <stdio.h>

int	main(void)
{
	int	x;

	x = 10;
	{
		int	x;

		x = 99;
		printf("%d\n", x);
	}
	printf("%d\n", x);
	return (0);
}

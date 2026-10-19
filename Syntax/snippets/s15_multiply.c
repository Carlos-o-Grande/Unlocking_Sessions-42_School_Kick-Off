#include <stdio.h>

int	main(void)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	r;

	a = 0x3;
	b = 0x5;
	r = 0;
	while (b != 0)
	{
		if (b & 1)
			r += a;
		a <<= 1;
		b >>= 1;
	}
	printf("%u\n", r);
	return (0);
}

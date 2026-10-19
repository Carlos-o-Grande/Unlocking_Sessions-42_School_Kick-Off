#include <stdio.h>

int	main(void)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	carry;

	a = 0x5;
	b = 0x3;
	while (b != 0)
	{
		carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	printf("%u\n", a);
	return (0);
}

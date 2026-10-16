#include <stdio.h>

int	main(void)
{
	int	n;
	int	upper;
	int	lower;

	n = 0x42;
	upper = (n >> 4) & 0x0F;
	lower = n & 0x0F;
	printf("hex:          0x%02X\n", n);
	printf("decimal:      %d\n", n);
	printf("upper nibble: %d\n", upper);
	printf("lower nibble: %d\n", lower);
	return (0);
}

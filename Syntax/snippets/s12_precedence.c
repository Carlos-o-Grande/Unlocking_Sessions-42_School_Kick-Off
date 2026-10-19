#include <stdio.h>

int	main(void)
{
	int	a;
	int	b;
	int	c;
	int	x;
	int	arr[2];
	int	*ptr;

	a = 4;
	b = 2;
	printf("a & b == 0  means a & (b == 0): %d\n", a & (b == 0));
	printf("you meant         (a & b) == 0: %d\n", (a & b) == 0);
	arr[0] = 10;
	arr[1] = 20;
	ptr = arr;
	x = *ptr++;
	printf("*ptr++ read %d, ptr now points at %d\n", x, *ptr);
	b = 3;
	c = 3;
	a = b == c;
	printf("a = b == c  gives a = %d\n", a);
	x = 5;
	printf("!x + 1 = %d, !(x + 1) = %d\n", !x + 1, !(x + 1));
	return (0);
}

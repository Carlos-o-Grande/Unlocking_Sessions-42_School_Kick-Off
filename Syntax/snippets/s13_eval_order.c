#include <stdio.h>

int	f(void)
{
	printf("f ");
	return (1);
}

int	g(void)
{
	printf("g ");
	return (2);
}

int	show(int a, int b)
{
	return (a + b);
}

int	main(void)
{
	show(f(), g());
	printf("\n");
	return (0);
}

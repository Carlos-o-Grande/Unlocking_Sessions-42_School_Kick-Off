#include <stdio.h>

int	main(void)
{
	int		a;
	int		b;
	float	result;

	a = 7;
	b = 2;
	result = a / b;
	printf("a / b        = %f\n", result);
	result = (float)a / b;
	printf("(float)a / b = %f\n", result);
	return (0);
}

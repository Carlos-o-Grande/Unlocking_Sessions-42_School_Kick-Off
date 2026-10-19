#include <stdio.h>

int	count_calls(void)
{
	static int	calls;

	calls++;
	return (calls);
}

int	main(void)
{
	printf("%d\n", count_calls());
	printf("%d\n", count_calls());
	printf("%d\n", count_calls());
	return (0);
}

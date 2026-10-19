#include <stdio.h>
#include <stddef.h>

int	process(char *s, int len)
{
	int	result;

	result = 0;
	if (s)
	{
		if (len > 0)
		{
			result = 1;
		}
	}
	return (result);
}

int	main(void)
{
	printf("%d\n", process("abc", 3));
	printf("%d\n", process(NULL, 3));
	printf("%d\n", process("abc", 0));
	return (0);
}

#include <stdio.h>
#include <stddef.h>

int	process(char *s, int len)
{
	if (!s || len <= 0)
		return (0);
	return (1);
}

int	main(void)
{
	printf("%d\n", process("abc", 3));
	printf("%d\n", process(NULL, 3));
	printf("%d\n", process("abc", 0));
	return (0);
}

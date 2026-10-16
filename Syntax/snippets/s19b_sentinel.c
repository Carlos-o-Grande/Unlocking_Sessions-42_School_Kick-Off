// args: hello 42 world
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		arr[6];
	int		*ptr;
	char	**arg;

	(void)argc;
	arr[0] = 10;
	arr[1] = 20;
	arr[2] = 30;
	arr[3] = 40;
	arr[4] = 50;
	arr[5] = 0;
	ptr = arr;
	while (*ptr)
	{
		printf("%d\n", *ptr);
		ptr++;
	}
	arg = argv + 1;
	while (*arg)
	{
		printf("%s\n", *arg);
		arg++;
	}
	return (0);
}

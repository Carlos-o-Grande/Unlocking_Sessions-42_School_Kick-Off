#include <stdio.h>

void	handle_overflow(void)
{
	printf("too many players\n");
}

int	main(void)
{
	char	buf[1024];
	int		limit;
	int		count;

	limit = 42;
	count = 50;
	printf("buffer %zu bytes, limit %d\n", sizeof(buf), limit);
	if (count > 42)
		handle_overflow();
	return (0);
}

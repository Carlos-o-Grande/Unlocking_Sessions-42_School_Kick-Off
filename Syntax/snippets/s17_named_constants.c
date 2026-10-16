#include <stdio.h>

#define BUFFER_SIZE  1024
#define MAX_PLAYERS  42

void	handle_overflow(void)
{
	printf("too many players\n");
}

int	main(void)
{
	char	buf[BUFFER_SIZE];
	int		limit;
	int		count;

	limit = MAX_PLAYERS;
	count = 50;
	printf("buffer %zu bytes, limit %d\n", sizeof(buf), limit);
	if (count > MAX_PLAYERS)
		handle_overflow();
	return (0);
}

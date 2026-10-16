#include <stdio.h>

int	main(void)
{
	int	row;
	int	col;

	row = 0;
	while (row < 3)
	{
		col = 0;
		while (col < 4)
		{
			printf("[%d,%d] ", row, col);
			col++;
		}
		printf("\n");
		row++;
	}
	return (0);
}

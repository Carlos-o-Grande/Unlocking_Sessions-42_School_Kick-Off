#include <stdio.h>
#include <stddef.h>

typedef struct s_node
{
	int	value;
}	t_node;

void	do_something(void)
{
	printf("value is 42\n");
}

int	main(void)
{
	t_node	node;
	t_node	*ptr;

	node.value = 42;
	ptr = &node;
	if (ptr && ptr->value == 42)
		do_something();
	ptr = NULL;
	if (ptr && ptr->value == 42)
		do_something();
	printf("safe check done, now without the NULL check:\n");
	fflush(stdout);
	if (ptr->value == 42)
		do_something();
	return (0);
}

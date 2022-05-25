#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
int	main(int ac, char **av, char **ev)
{
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	while (ev[i])
	{
		printf("%s\n",ev[i++]);
	}
	return (0);
}

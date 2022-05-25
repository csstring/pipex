#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int	main(void)
{
	char *str;
	size_t	i;
	int	rev;
	int fd;

	i = 0;
	fd = open("dup2_test", O_RDWR);
	dup2(fd, STDOUT_FILENO);
	str = (char *)malloc(sizeof(char)*2147483647);
	while (i < 2147483646)
	{
		str[i] = 's';
		i++;
	}
	str[i] = '\0';
	rev = printf("%s", str);
	printf("\n%d", rev);
	return (0);
}

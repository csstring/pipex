#include <unistd.h>
#include <stdio.h>
#include "./includes/libft.h"
#include <fcntl.h>
void	ft_parent_exe()
{
	char	*str[] = {"grep", "l", "test.txt", NULL};

	execve("/usr/bin/grep",str,NULL);
}

void	ft_child_exe()
{
	char	*str[] = {"cat", "-e", NULL};

	execve("/bin/cat", str, NULL);
}
int	main(int ac, char **av, char **ev)
{
	int fd[2];
	pid_t pid;
	int	temp;

	ft_ev_parsing(ev);
	pipe(fd);
	pid = fork();
	if (pid > 0)//parent
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_parent_exe();
		wait(NULL);
	}
	else //child
	{
		temp = open("outfile", O_RDWR);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(temp, STDOUT_FILENO);
		ft_child_exe();
	}
	return (0);
}

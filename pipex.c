#include "pipex.h"

void	ft_parent(int *fd, t_pipex *val, char **argv)
{
	int	temp;

	//close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	temp = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	dup2(temp, STDOUT_FILENO);
	close(temp);
	if (val -> exe_path[1] == 0)
		exit(0);
	execve(val -> exe_path[1], val -> cmd2, val -> ev);
}

void	ft_child(int *fd, t_pipex *val, char **argv)
{
	int	temp;

	//close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	temp = open(argv[1], O_RDONLY);
	dup2(temp, STDIN_FILENO);
	close(temp);
	if (val -> exe_path[0] == 0)
		exit(0);
	execve(val -> exe_path[0], val -> cmd1, val -> ev);
}

#include <unistd.h>
#include <stdio.h>
#include "./includes/libft.h"
#include <fcntl.h>
#include "pipex.h"
void	ft_parent_exe(t_pipex *val)
{
	execve(val -> exe_path[1], val -> cmd2, NULL);
}

void	ft_child_exe(t_pipex *val)
{
	execve(val -> exe_path[0], val -> cmd1, NULL);
}

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(0);
}
int	ft_access_check(char *cmd, t_pipex *val)
{
	char	*temp;
	char	*str;
	int		i;

	i = 0;
	while (val -> ev[i])
	{
		temp = ft_strjoin(val -> ev[i], "/");
		str = ft_strjoin(temp, cmd);
		free(temp);
		if (access(str, F_OK) == 0)
			if (access(str, X_OK) == 0)
			{
				if (val -> exe_path[0] == 0)
					val -> exe_path[0] = str;
				else
					val -> exe_path[1] = str;
				return (0);
			}
		free(str);
		i++;
	}
	ft_error("ERROR: permission denined or file is not exist");
	return (0);
}
void	ft_av_parsing(char **argv, t_pipex *val)
{
	val -> cmd1 = ft_split(argv[2], ' ');
	val -> cmd2 = ft_split(argv[3], ' ');
}
char	**ft_ev_parsing(char **enpv)
{
	char	*str;
	char	**line;
	int		i;

	i = 0;
	while (enpv[i] != NULL)
	{
		str = ft_strnstr(enpv[i++], "PATH=", 5);
		if (str != NULL)
		{
			str = ft_strtrim(str, "PATH=");
			line = ft_split(str, ':');
			free(str);
			return (line);
		}
	}
	ft_error("ERROR : env don't have PATH");
	return (0);
}

void	ft_pipex(char **argv, t_pipex *val)
{
	int		fd[2];
	pid_t	pid;
	int		temp;
	char	c;

	pipe(fd);
	pid = fork();
	if (pid == 0)//child
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		temp = open(argv[1], O_RDONLY);
		while (read(temp, &c, 1))
			write(STDOUT_FILENO, &c, 1);
		execve(val -> exe_path[0], val -> cmd1, NULL);
		//ft_child_exe(val);
	}
	else //parent
	{
		temp = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(temp, STDOUT_FILENO);
		ft_parent_exe(val);
	}
}

int	main(int ac, char **av, char **enpv)
{
	t_pipex val;
	int	i;

	i = 0;
	if (ac != 5)
		return (0);
	val.ev = ft_ev_parsing(enpv);
	ft_av_parsing(av, &val);
	ft_access_check(val.cmd1[0], &val);
	ft_access_check(val.cmd2[0], &val);
	printf("%s\n",val.cmd1[0]);
	printf("%s\n",val.cmd1[1]);
	printf("%s",val.cmd1[2]);
	//ft_pipex(av, &val);
	return (0);
}

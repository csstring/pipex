#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include "pipex.h"

int	ft_access_check(char *cmd, t_pipex *val, int check)
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
				val -> exe_path[check] = str;
				return (0);
			}
		free(str);
		i++;
	}
	perror("file access error ");
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
	perror("ENV PATH error ");
	return (0);
}

void	ft_pipex(char **argv, t_pipex *val)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork error ");
		exit(0);
	}
	if (pid == 0)//child
	{
		close(fd[0]);
		ft_child(fd, val, argv);
		close(fd[1]);
	}
	else if (pid > 0)//parent
	{
		close(fd[1]);
		wait(NULL);
		ft_parent(fd, val, argv);
		close(fd[0]);
	}
}

int	main(int ac, char **av, char **enpv)
{
	t_pipex val;
	int	i;

	i = 0;
	if (ac != 5)
	{
		perror("wrong input count");
		return (0);
	}
	val.ev = ft_ev_parsing(enpv);
	ft_av_parsing(av, &val);
	ft_access_check(val.cmd1[0], &val, 0);
	ft_access_check(val.cmd2[0], &val, 1);
	ft_pipex(av, &val);
	return (0);
}

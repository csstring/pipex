/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:05:12 by schoe             #+#    #+#             */
/*   Updated: 2022/06/04 21:14:20 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

void	ft_parent(int *fd, t_pipex *val, char **argv, char **enpv)
{
	int	temp;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	temp = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (temp < 0)
	{
		perror("open error : ");
		exit(1);
	}
	dup2(temp, STDOUT_FILENO);
	close(temp);
	if (val -> exe_path[1] == 0)
		exit(1);
	execve(val -> exe_path[1], val -> cmd2, enpv);
}

void	ft_child(int *fd, t_pipex *val, char **argv, char **enpv)
{
	int	temp;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	temp = open(argv[1], O_RDONLY);
	if (temp < 0)
	{
		perror("open error : ");
		exit(1);
	}
	dup2(temp, STDIN_FILENO);
	close(temp);
	if (val -> exe_path[0] == 0)
		exit(1);
	execve(val -> exe_path[0], val -> cmd1, enpv);
}

void	ft_pipex(char **argv, t_pipex *val, char **enpv)
{
	int		fd[2];
	pid_t	pid;
	int		st;

	if (pipe(fd) < 0)
	{
		perror("pipe error ");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork error ");
		exit(1);
	}
	if (pid == 0)
		ft_child(fd, val, argv, enpv);
	else if (pid > 0)
	{
		waitpid(pid, &st, WNOHANG);
		ft_parent(fd, val, argv, enpv);
	}
}

int	main(int ac, char **av, char **enpv)
{
	t_pipex	val;
	int		i;

	i = 0;
	if (ac != 5)
	{
		perror("wrong input count");
		exit(1);
	}
	val.ev = ft_ev_parsing(enpv);
	ft_av_parsing(av, &val);
	ft_access_check(val.cmd1[0], &val, 0);
	ft_access_check(val.cmd2[0], &val, 1);
	ft_pipex(av, &val, enpv);
	return (0);
}

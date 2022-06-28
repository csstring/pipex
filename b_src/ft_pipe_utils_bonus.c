/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:53:22 by schoe             #+#    #+#             */
/*   Updated: 2022/06/20 14:36:06 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_make_pipe(t_input *input, t_pipex *val)
{
	int	ac_temp;
	int	i;

	i = 0;
	ac_temp = input->ac;
	val->fd = (int **)malloc(sizeof(int *) * ac_temp - 4);
	if (val->fd == NULL)
		exit(1);
	while (ac_temp - 4 > 0)
	{
		(val->fd)[i] = (int *)malloc(sizeof(int) * 2);
		if (val->fd[i] == NULL)
			exit(1);
		if (pipe(val->fd[i]) == -1)
		{
			perror("pipe error ");
			exit(1);
		}
		i++;
		ac_temp--;
	}
	val->end = i;
}

static void	ft_close_fd2(t_pipex *val, int i, int end_temp)
{
	if (i == val->end)
	{
		while (i - 2 >= 0)
		{
			close(val->fd[i - 2][P_W]);
			close(val->fd[i - 2][P_R]);
			i--;
		}
	}
	else
	{
		while (end_temp > 0)
		{
			end_temp--;
			if (end_temp == i || end_temp == i - 1)
				continue ;
			close(val->fd[end_temp][P_W]);
			close(val->fd[end_temp][P_R]);
		}
	}
}

void	ft_close_fd(pid_t pid, t_pipex *val, int i)
{
	int	end_temp;

	end_temp = val->end;
	if (pid > 0)
	{
		while (end_temp > 0)
		{
			end_temp--;
			close(val->fd[end_temp][P_W]);
			close(val->fd[end_temp][P_R]);
		}
	}
	else if (i == 0)
	{
		while (end_temp > 1)
		{
			end_temp--;
			close(val->fd[end_temp][P_W]);
			close(val->fd[end_temp][P_R]);
		}
	}
	else
		ft_close_fd2(val, i, end_temp);
}

static void	ft_pipex2(pid_t pid, t_input *input, t_pipex *val, int i)
{
	if (pid == 0 && i == 0)
		ft_cmd_start(i, val, input);
	else if (pid == 0 && i == val->end)
		ft_cmd_end(i, val, input);
	else if (pid == 0)
		ft_cmd_mid1(i, val, input);
}

int	ft_pipex(int ac, t_input *input, t_pipex *val)
{
	pid_t	pid;
	int		i;
	int		st;

	i = 0;
	while (ac > 3)
	{
		ac--;
		pid = fork();
		if (pid == -1)
		{
			perror("fork error ");
			exit(1);
		}
		if (pid == 0)
			break ;
		i++;
	}
	ft_close_fd(pid, val, i);
	ft_pipex2(pid, input, val, i);
	waitpid(pid, &st, 0);
	if (val->check == 1)
		unlink(".temp");
	return (st >> 8 & 0x000000ff);
}

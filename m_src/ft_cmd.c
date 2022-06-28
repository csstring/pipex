/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c 		                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:52:52 by schoe             #+#    #+#             */
/*   Updated: 2022/06/20 13:09:38 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include "libft.h"
#include <stdio.h>

void	ft_cmd_end(int i, t_pipex *val, t_input *input)
{
	int	temp;

	close(val->fd[i - 1][P_W]);
	dup2(val->fd[i - 1][P_R], STDIN_FILENO);
	close(val->fd[i - 1][P_R]);
	temp = open(input->av[input->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (temp < 0)
	{
		perror("open error : ");
		exit(1);
	}
	dup2(temp, STDOUT_FILENO);
	close(temp);
	ft_error_check(i, input, val);
	execve(val->exe_path[i], val->cmd[i], input->ev);
}

void	ft_cmd_mid1(int i, t_pipex *val, t_input *input)
{
	close(val->fd[i - 1][P_W]);
	close(val->fd[i][P_R]);
	dup2(val->fd[i - 1][P_R], STDIN_FILENO);
	close(val->fd[i - 1][P_R]);
	dup2(val->fd[i][P_W], STDOUT_FILENO);
	close(val->fd[i][P_W]);
	ft_error_check(i, input, val);
	execve(val -> exe_path[i], val -> cmd[i], input->ev);
}

void	ft_cmd_start(int i, t_pipex *val, t_input *input)
{
	int	temp;

	close(val->fd[i][P_R]);
	dup2(val->fd[i][P_W], STDOUT_FILENO);
	close(val->fd[i][P_W]);
	temp = open(input->av[1], O_RDONLY);
	if (temp < 0)
	{
		perror("open error : ");
		exit(1);
	}
	dup2(temp, STDIN_FILENO);
	close(temp);
	ft_error_check(i, input, val);
	execve(val -> exe_path[i], val -> cmd[i], input->ev);
}

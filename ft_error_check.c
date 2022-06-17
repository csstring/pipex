/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:58:20 by schoe             #+#    #+#             */
/*   Updated: 2022/06/17 20:49:36 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <string.h>

static void	ft_check_file(int i,t_pipex *val, t_input *input)
{
	int	j;

	j = 0;
	while (val->cmd[i][0][j] != 0)
	{
		if (val->cmd[i][0][j] == '/')
		{
			ft_eprintf("bash: %s: %s\n",input->av[i + val->check + 2] ,strerror(2));
			exit(2);
		}
		j++;
	}
}

static int	ft_check_dir(int i, t_pipex *val, t_input *input)
{
	int	j;
	int	dot_count;

	j = 0;
	dot_count = 0;
	while (val->cmd[i][0][j] != 0)
	{
		if (val->cmd[i][0][j] != '/' && val->cmd[i][0][j] != '.')
			return (0);
		if (val->cmd[i][0][j] == '.')
			dot_count++;
		else if (val->cmd[i][0][j] == '/')
			dot_count = 0;
		if (dot_count > 2)
			return (0);
		j++;
	}
	ft_eprintf("bash: %s: %s\n",input->av[i + val->check + 2] ,strerror(21));
	exit(21);
}

void	ft_error_check(int i, t_input *input, t_pipex *val)
{
	if (input->av[i + val->check + 2][0] == 0)
	{
		ft_eprintf("bash: : command not found\n");
		exit(127);
	}
	ft_check_dir(i, val, input);
	if (val->exe_path[i] == NULL)
	{
		ft_check_file(i, val, input);
		ft_eprintf("bash: %s: command not found\n", input->av[i + val->check + 2]);
		exit(127);
	}
}

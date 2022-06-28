/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:53:16 by schoe             #+#    #+#             */
/*   Updated: 2022/06/20 14:59:16 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <stdio.h>

static int	ft_access_check2(char *cmd, t_pipex *val, int check, int i)
{
	char	*temp;
	char	*str;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
	{
		val->exe_path[check] = cmd;
		return (0);
	}
	else
	{
		temp = ft_strjoin(val -> ev[i], "/");
		str = ft_strjoin(temp, cmd);
		free(temp);
		if (access(str, F_OK) == 0 && access(str, X_OK) == 0)
		{
			val -> exe_path[check] = str;
			return (0);
		}
		free(str);
	}
	return (1);
}

int	ft_access_check(char *cmd, t_pipex *val, int check)
{
	int		i;

	i = 0;
	if (cmd == NULL)
	{
		val->exe_path[check] = NULL;
		return (0);
	}
	while (val -> ev[i])
	{
		if (ft_access_check2(cmd, val, check, i) == 0)
			return (0);
		i++;
	}
	val->exe_path[check] = NULL;
	return (0);
}

void	ft_av_parsing(t_input *input, t_pipex *val)
{
	int	ac_temp;
	int	i;

	i = 0;
	ac_temp = input->ac;
	while (ac_temp > 3)
	{
		if (ft_strncmp(input->av[i + 2 + val->check], "awk ", 4) == 0 || \
				ft_strncmp(input->av[i + 2 + val->check], "sed ", 4) == 0)
		{
			val -> cmd[i] = ft_split(input->av[i + 2], '\'');
			val -> cmd[i][0] = ft_strtrim(val -> cmd[i][0], " ");
		}
		else
			val -> cmd[i] = ft_split(input->av[i + 2 + val->check], ' ');
		i++;
		ac_temp--;
	}	
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

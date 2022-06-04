/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:06:11 by schoe             #+#    #+#             */
/*   Updated: 2022/06/04 21:11:14 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

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
		{
			if (access(str, X_OK) == 0)
			{
				val -> exe_path[check] = str;
				return (0);
			}
		}
		free(str);
		i++;
	}
	perror("commnd error ");
	return (0);
}

void	ft_av_parsing(char **argv, t_pipex *val)
{
	if (ft_strncmp(argv[2], "awk", 3) == 0)
	{
		val -> cmd1 = ft_split(argv[2], '\'');
		val -> cmd1[0] = ft_strtrim(val -> cmd1[0], " ");
	}
	else
		val -> cmd1 = ft_split(argv[2], ' ');
	if (ft_strncmp(argv[3], "awk", 3) == 0)
	{
		val -> cmd2 = ft_split(argv[3], '\'');
		val -> cmd2[0] = ft_strtrim(val -> cmd2[0], " ");
	}
	else
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

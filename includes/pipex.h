/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:06:10 by schoe             #+#    #+#             */
/*   Updated: 2022/06/04 21:10:03 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_pipex
{
	char	**ev;
	char	**cmd1;
	char	**cmd2;
	char	*exe_path[2];
}	t_pipex;

void	ft_parent(int *fd, t_pipex *val, char **argv, char **enpv);
void	ft_child(int *fd, t_pipex *val, char **argv, char **enpv);
void	ft_pipex(char **argv, t_pipex *val, char **enpv);

int		ft_access_check(char *cmd, t_pipex *val, int check);
void	ft_av_parsing(char **argv, t_pipex *val);
char	**ft_ev_parsing(char **enpv);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:06:10 by schoe             #+#    #+#             */
/*   Updated: 2022/05/26 22:24:13 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#include <unistd.h>
#include <stdio.h>
#include "./includes/libft.h"
#include <fcntl.h>
#include "pipex.h"

typedef struct s_pipex
{
	char	**ev;
	char	**cmd1;
	char	**cmd2;
	char	*exe_path[2];
}	t_pipex;

void	ft_parent(int *fd, t_pipex *val, char **argv);
void	ft_child(int *fd, t_pipex *val, char **argv);

#endif

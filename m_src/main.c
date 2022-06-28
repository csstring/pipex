/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:05:12 by schoe             #+#    #+#             */
/*   Updated: 2022/06/20 14:29:19 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include "libft.h"

void	ft_init(t_pipex *val, t_input *input)
{
	val->exe_path = (char **)malloc(sizeof(char *) * (input->ac - 2));
	val->cmd = (char ***)malloc(sizeof(char **) * (input->ac - 2));
	if (!val->cmd || !val->exe_path)
		exit(1);
	val->cmd[input->ac - 3] = NULL;
	val->exe_path[input->ac - 3] = NULL;
}

int	main(int ac, char **av, char **enpv)
{
	t_pipex	val;
	t_input	input;
	int		i;

	i = 0;
	if (ac != 5)
	{
		ft_eprintf("error : wrong input\n");
		return (1);
	}
	input.ac = ac;
	input.av = av;
	input.ev = enpv;
	ft_init(&val, &input);
	val.ev = ft_ev_parsing(input.ev);
	ft_av_parsing(&input, &val);
	while (val.cmd[i])
	{
		ft_access_check(val.cmd[i][0], &val, i);
		i++;
	}
	ft_make_pipe(&input, &val);
	return (ft_pipex(input.ac, &input, &val));
}

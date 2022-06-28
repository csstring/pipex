/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:05:12 by schoe             #+#    #+#             */
/*   Updated: 2022/06/20 14:55:28 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#include "libft.h"

void	ft_here_doc(t_input *input)
{
	int		temp;
	char	*input_str;
	char	*str;
	int		check;

	input_str = ft_strjoin(input->av[2], "\n");
	temp = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	dup2(temp, STDOUT_FILENO);
	check = 0;
	while (1)
	{
		str = get_next_line(0);
		if (str != NULL && ft_strrchr(str, '\n') != NULL)
			check = 1;
		if ((check == 1 && str == NULL) || (str != NULL && \
					!ft_strncmp(input_str, str, ft_strlen(input_str) + 1)))
			break ;
		if (check == 0 && str == NULL)
			continue ;
		write(1, str, ft_strlen(str));
		free(str);
	}
	close(temp);
	free(str);
	free(input_str);
}

void	ft_init(t_pipex *val, t_input *input)
{
	val->check = 0;
	if (!ft_strncmp(input->av[1], "here_doc", 9) && \
			access("here_doc", F_OK == -1))
	{
		(input->ac)--;
		val->check = 1;
	}
	if (input->ac < 5)
	{
		ft_eprintf("error : wrong input\n");
		exit(1);
	}
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
	if (ac < 5)
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
	if (val.check)
		ft_here_doc(&input);
	return (ft_pipex(input.ac, &input, &val));
}

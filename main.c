/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:05:12 by schoe             #+#    #+#             */
/*   Updated: 2022/06/16 21:54:38 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include "libft.h"
void	ft_here_doc(t_input *input)
{
	int		temp;
	char	*input_str;
	char	*str;
	int		check;

	input_str = ft_strjoin(input->av[2], "\n");
	temp = open(input->av[1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	dup2(temp, STDOUT_FILENO);
	check = 0;
	while (1)
	{
		str = get_next_line(0);
		if (str != NULL && ft_strrchr(str, '\n') != NULL)
			check = 1;
		//ctrl+d일때 루프 돌려야하나 아니면 재시작?
		if((check == 1 && str == NULL) || (str != NULL && !ft_strncmp(input_str, str, ft_strlen(input_str) + 1)))
			break ;
		if (check == 0 && str == NULL)
			continue ;
		write(1, str, ft_strlen(str));
		free(str);
	}
	close(temp);
	free(input_str);
}

void	ft_close_fd(pid_t pid, t_pipex *val, int i)
{
	int	end_temp;

	end_temp = val->end;
	if (pid > 0)
		while (end_temp > 0)
		{
			end_temp--;
			close(val->fd[end_temp][P_W]);
			close(val->fd[end_temp][P_R]);
		}
	else if (i == 0)
		while (end_temp > 1)
		{
			end_temp--;
			close(val->fd[end_temp][P_W]);
			close(val->fd[end_temp][P_R]);
		}
	else if	(i == val->end)
		while (i - 2 >= 0)
		{
			close(val->fd[i - 2][P_W]);
			close(val->fd[i - 2][P_R]);
			i--;
		}	
	else
		while (end_temp > 0)
		{
			end_temp--;
			if (end_temp == i || end_temp == i - 1)
				continue ;
			close(val->fd[end_temp][P_W]);
			close(val->fd[end_temp][P_R]);
		}
}

void	ft_pipex(int ac , t_input *input, t_pipex *val)
{
	pid_t	pid;
	int		i;
	int		st;

	i = 0;
	while (ac > 3)
	{
		ac--;
		pid = fork();
		if (pid == 0)
			break ;
		i++;
	}
	ft_close_fd(pid, val, i);
	if (pid == 0 && i == 0)
		ft_cmd_start(i, val, input);
	else if (pid == 0 && i == val->end)
		ft_cmd_end(i, val, input);
	else if (pid == 0)
		ft_cmd_mid1(i, val, input);
	else
	{
		waitpid(pid, &st, 0);
		if (val->check == 1)
			unlink("here_doc");
	}
}

void	ft_make_pipe(t_input *input, t_pipex *val)
{
	int	ac_temp;
	int	i;

	i = 0;
	ac_temp = input->ac;
	val->fd = (int **)malloc(sizeof(int *) * ac_temp - 4);
	while (ac_temp - 4 > 0)
	{
		(val->fd)[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(val->fd[i]))
		{
			perror("pipe error ");
			exit(1);
		}
		i++;
		ac_temp--;
	}
	val->end = i;
}

void	ft_init(t_pipex *val, t_input *input)
{
	val->check = 0;
	if (!ft_strncmp(input->av[1], "here_doc", 9) && access("here_doc", F_OK == -1))
	{
		(input->ac)--;
		val->check = 1;
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
		perror("wrong input count");
		exit(1);
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
	ft_pipex(input.ac, &input, &val);
	return (0);
}

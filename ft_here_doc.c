void	ft_here_doc(t_input *input, t_pipex *val)
{
	int		temp;
	char	*input_str;
	char	*str;

	input_str = ft_strjoin(input->av[2], "\n");
	temp = open(input->av[1], O_WONLY | O_CREAT | O_TURNC, 0664);
	dup2(temp, STDOUT_FILENO);
	while (!ft_strncmp(input_str, str, ft_strlen(input_str) + 1))
	{
		str = get_next_line(0);
		if(!ft_strncmp(input_str, str, ft_strlen(input_str) + 1))
			break ;
		free(str);
	}
	free(input_str);
}

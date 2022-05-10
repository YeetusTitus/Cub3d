
int	arg_error(int argc, char **argv)
{
	int	i;

	i = ft_strlen_v2(argv[1]);
	if (argc > 2)
		return (1);
	if (argv[1][i] != 'b' || argv[1][i - 1] != 'u'
		|| argv[1][i - 2] != 'c' || argv[1][i - 3] != '.')
		return (1);
	if (check_map(argv[1]) != 0)
		return (check_map(argv[1]));
    return (0);
}

int	check_map(char **argv)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(argv[1]);
	if (fd < 0)
		return (2);
	line = get_next_line(fd);
	while (line[i++])
		if (line[i] != '1')
			return (3);
	while (line)
	{
		line = get_next_line(fd);
		if (line[0] != '1' || line[ft_strlen_v2(line)] != '1')
			return (3);
	}
	return (0);
}
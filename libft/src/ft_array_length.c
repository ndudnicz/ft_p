int		ft_array_length(char const **array)
{
	int		i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

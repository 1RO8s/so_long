/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/21 10:39:13 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*read_mapfile(char *file_name)
{
	int		fd;
	char	*line;
	char	*old_map;
	char	*map;

	old_map = NULL;
	map = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		perror("Error\nファイルを開けませんでした");
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map = ft_strjoin(old_map, line);
		if (old_map != NULL)
			free(old_map);
		old_map = ft_strdup(map);
	}
	close(fd);
	return (map);
}

/**
 * Return 1 if wrong arguments are entered
 * @param[in]  argc  number of arguments
 * @param[in]  argv each argument's value
 */
int	arg_check(int argc, char *argv[])
{
	int		len;
	char	*ext;
	char	*filename;

	if (argc != 2)
	{
		ft_printf("Error\n引数が正しくありません\n");
		return (1);
	}
	filename = argv[1];
	len = ft_strlen(filename);
	ext = &filename[len - 4];
	if (ft_strncmp(".ber", ext, 4))
	{
		ft_printf("Error\n.berファイルを指定してください\n");
		return (1);
	}
	return (0);
}

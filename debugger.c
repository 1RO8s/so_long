/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/11 06:01:05 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	show_stat(t_game *g, int num)
{
	printf("\n#%d x,y => (%d, %d)", num, g->player->x, g->player->y);
	printf(" [%p,%p]\n", &(g->player->x), &(g->player->y));
}

void	test_render_map(t_game *g, int i, int j)
{
	char	*map;

	map = g->map;
	if (g->map[(g->width + 1) * j + i] == '\n')
		printf("\n");
	if (map[(g->width + 1) * j + i] == '1')
		printf("壁");
	else if (map[(g->width + 1) * j + i] == 'C')
		printf("収");
	else if (map[(g->width + 1) * j + i] == 'E')
		printf("出");
	if (map[(g->width + 1) * j + i] == '0')
		printf("　");
}

void	show_game_info(t_game *g)
{
	printf("_/_/_/_/_/ game info _/_/_/_/_/\n");
	printf("width:%d height:%d\n", g->width, g->height);
	printf("items left:%d\n", g->item_count);
	printf("player:%d,%d\n", g->player->x, g->player->y);
	printf("exit:%d,%d\n", g->exit->x, g->exit->y);
}

// char	*read_mapfile(void)
// {
// 	char	*map;

// 	printf("\n--- read_mapfile ---\n");
// 	map = (char *)malloc(sizeof(char) * BUFFER_SIZE);
// 	if (map == NULL)
// 	{
// 		// メモリ割り当てエラーの処理
// 		return (NULL);
// 	}
// 	strcpy(map,
// 			"1111111111\n"
// 			"1P00000CC1\n"
// 			"1001CC1CC1\n"
// 			"1CC1CC1001\n"
// 			"1CC00000E1\n"
// 			"1111111111");
// 	return (map);
// }

void	*my_malloc(size_t size)
{
	void	*ptr;

	#undef malloc
	ptr = malloc(size);
	#define malloc(size) my_malloc(size)
	// printf("\n%p:malloc\n", ptr);
	return (ptr);
}

void	my_free(void *ptr)
{
	// printf("\n%p:free\n", ptr);
	#undef free
	free(ptr);
	# define free(size) my_free(size)
}

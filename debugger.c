/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 05:57:37 by hnagasak          #+#    #+#             */
/*   Updated: 2023/09/05 06:15:57 by hnagasak         ###   ########.fr       */
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

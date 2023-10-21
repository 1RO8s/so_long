/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 07:59:50 by hnagasak          #+#    #+#             */
/*   Updated: 2023/10/21 10:41:08 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// # include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

# define BUFFER_SIZE 1000
# define TILE_SIZE 32

# define TRUE 1
# define FALSE 0

// # define malloc(size) my_malloc(size)
// # define free(size) my_free(size)

typedef struct s_position
{
	int			x;
	int			y;
	int			direction;
}				t_position;

typedef struct s_images
{
	void		*img_wall;
	void		*img_space[10];
	void		*img_item;
	void		*img_player;
	void		*img_exit;
}				t_images;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	t_images	*images;
	t_position	*player;
	t_position	*exit;
	char		*map;
	int			item_count;
	int			move_count;
	int			errno;
	int			completed;
}				t_game;

/**
 * @struct t_count
 * @brief Structure for counting elements in map
**/
typedef struct s_count
{
	int			item;
	int			exit;
	int			player;
}				t_count;

# define NOT_RECTANGLE 201
# define NO_PLAYER_POSITION 202
# define NO_EXIT_POSITION 203
# define NO_ITEMS 204
# define NOT_WALLED 205
# define UNREACHABLE_EXIT 206
# define UNCOLLECTIBLE_ITEM 207
# define INVALID_ELEMENT 208

// so_long.c
int				is_invalid_map(t_game *g);
int				destroy_window(t_game *game);

// renderer.c
// void			render_player(t_game *game);
// void			render_map(t_game *game);
int				render(t_game *game);

// controler.c
int				press_keys(int kcd, t_game *game);
void			move_player(t_game *game, int keycode);

// element_count.c
int				has_required_elements(t_game *g);

//  arg_check.c
char			*read_mapfile(char *file_name);
int				arg_check(int argc, char *argv[]);

// util.c
t_position		*cps(int x, int y);
int				destroy_window(t_game *game);
void			print_errmsg(t_game *game);
void			*read_img(t_game *g, char *file, int *width, int *height);
int				is_invalid_element(char c);

// libft
int				ft_printf(const char *format, ...);
char			*get_next_line(int fd);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
void			*ft_memset(void *b, int c, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

// debugger.c
void			show_stat(t_game *g, int num);
void			test_render_map(t_game *g, int i, int j);
void			show_game_info(t_game *g);
// void			*my_malloc(size_t size);
// void			my_free(void *);

#endif

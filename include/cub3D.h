/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:14:56 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/02 11:53:01 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "fcntl.h"
# include "math.h"
# include "stdio.h"
# include "unistd.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <string.h>

# define MAX_LINES 1000
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_ray
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_movement
{
	double		move_speed;
	double		rot_speed;
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			rot_left;
	int			rot_right;
}				t_movement;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			player_dir;
	int			p_n;
	int			p_s;
	int			p_e;
	int			p_w;
	int			cc;
	int			count;
}				t_player;

typedef struct s_data
{
	t_img		img;
	t_player	player;
	t_movement	movement;
	t_ray		ray;
	void		*mlx;
	void		*win;
	char		**map;
	char		**copie_map;
	int			map_width;
	int			map_height;
	void		*texture;
	char		*n_t;
	char		*s_t;
	char		*w_t;
	char		*e_t;
	int			f_color;
	int			c_color;
	int			no_loaded;
	int			so_loaded;
	int			we_loaded;
	int			ea_loaded;
	int			f_loaded;
	int			c_loaded;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*no_texture;
}				t_data;

/// parsing/parsing.c
void			count_map_elements(t_data *data, int *exit_count,
					int *start_count, int *collectible_count);
int				check_map_elements(t_data *data);
void			check_invalid_characters(t_data *data, char element);

/// check_extension/cub_extension.c
int				cub_extension(const char *filename);
int				check_arguments(int ac, char **av);

/// map/check_map.c
int				check_map_walls(t_data *data);
void			check_map(t_data *data);

/// utils/free.c

void			free_map(t_data *data);
void			ft_free_split(char **array);

// utils/errors.c

void			error_exit(const char *message);

/// check_file/parse_file.c

// int parse_texture_colors(t_data *data, char **lines);
int				parse_texture_colors(t_data *data, char **lines,
					const char *filename);
int				parse_cub(t_data *data, const char *filename);
int				parse_color(const char *line);
int				parse_map(t_data *data, char **lines);
int				validate_map(t_data *data, char **lines, int map_start);

void			init_texture_colors_flags(t_data *data);
int				verify_texture_and_colors(t_data *data);
int				parse_texture_line(t_data *data, char *line);
int				compare_loaded(t_data *data, char *line);
void			init_data(t_data *data);
int				parse_cub(t_data *data, const char *filename);
int				check_for_duplicates(t_data *data, const char *line);

// check_file/utils_file.c

int				ft_arraylen(char **array);
int				is_empty_line(const char *line);

//// check_file/check_valid_data_6elements.c

int				is_valid_texture_path(const char *path);
int				is_valid_color_format(const char *str);

// Ajout Liz partie

// raycasting/init_ray.c

void			init_ray_dir(t_ray *ray, t_data *data, int x);
void			init_ray_dist(t_ray *ray);
void			init_ray_step(t_ray *ray);

// raycasting/perform_daa.c

void			perform_dda(t_ray *ray, t_data *data);
void			calculate_wall_dist(t_ray *ray);
void			calculate_line_height(t_ray *ray);

// raycasting/raycasting.c

void			init_player_pos(t_ray *ray, t_data *data);
void			draw_vertical_line(t_data *data, t_ray *ray, int x);
void			raycasting(t_data *data);

// raycasting/vectors.c

void			set_direction_vectors(t_ray *ray, char dir);

// game/game_loop.c

int				game_loop(t_data *data);
void			init_hooks(t_data *data);
int				exit_game(t_data *data);

// game/clean.c

void			free_textures(t_data *data);
void			free_map_array(char **map, int height);
void			free_mlx_resources(t_data *data);
void			free_resources(t_data *data);

// controls/key_events.c

int				handle_keypress(int keycode, t_data *data);
int				handle_keyrelease(int keycode, t_data *data);

// controls/player_movement.c

void			handle_forward_movement(t_data *data);
void			handle_strafe_movement(t_data *data);

// controls/player_rotation.c

void			handle_rotation(t_data *data);
void			handle_rotation_left(t_data *data);

#endif
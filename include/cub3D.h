/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:14:56 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/13 13:22:18 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720


# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define MINIMAP_SIZE 200

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	char		player_dir;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
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
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			rot_left;
	int			rot_right;
	double		move_speed;
	double		rot_speed;
}				t_movement;

typedef struct s_texture {
    void    *img;
    int     height;
    int     width;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}				t_texture;

typedef struct s_minimap {
	double  scale;
    int     width;
    int     height;
    int     offset_x;
    int     offset_y;
}               t_minimap;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	char		*n_t;
	char		*s_t;
	char		*w_t;
	char		*e_t;
	// void		*no_texture;
	// void		*so_texture;
	// void		*we_texture;
	// void		*ea_texture;
	t_texture	*no_texture;
	t_texture	*so_texture;
	t_texture	*we_texture;
	t_texture	*ea_texture;
	char		**map;
	char		**copie_map;
	int			map_width;
	int			map_height;
	int			f_color;
	int			c_color;
	t_player	player;
	t_movement	movement;
	t_minimap   minimap;
}				t_data;

/* parsing_1.c */
void			init_data(t_data *data);
int				parse_texture(char *line, char **texture_path);
int				parse_color_identifier(char *line, int *color, char type);
int				parse_identifier(char *line, t_data *data);

/* parsing_2.c */
int				check_required_elements(t_data *data);
int				process_valid_line(char *line, t_data *data, int fd);
int				parse_file_content(int fd, t_data *data);
int				parse_file(char *filename, t_data *data);

/* utils_parsing.c */
int				check_file_extension(char *filename);
int				is_empty_line(char *line);
int				parse_color(char *str);
int				is_valid_map_char(char c);
int				is_valid_player_char(char c);

/* check_map.c */
int				validate_map(t_data *data);

/* texture_handler.c */
// int				load_texture(t_data *data, void **texture, char *path);
// int				load_texture(t_data *data, t_texture **texture, char *path);
int				load_all_texture(t_data *data);
int				init_textures(t_data *data);
// int				get_tex_color(void *texture, int x, int y);
int				get_tex_color(t_texture *texture, int tex_x, int tex_y);
int				get_wall_texture(t_data *data, t_ray *ray);
// int				get_tex_x(void *texture, t_ray *ray);
int				get_tex_x(t_texture *texture, t_ray *ray);

/* game_init.c */
void			init_window(t_data *data);
void			init_image(t_data *data);
int				init_game(t_data *data);
// void			exit_with_error(char *message, t_data *data);
void			put_pixel(t_data *data, int x, int y, int color);

/* game_loop.c */
int				game_loop(t_data *data);
void			init_hooks(t_data *data);
int				exit_game(t_data *data);

/* raycasting.c */
void			init_player_pos(t_ray *ray, t_data *data);
void			draw_vertical_line(t_data *data, t_ray *ray, int x);
void			raycasting(t_data *data);

/* init_ray.c */
void			init_ray_dir(t_ray *ray, t_data *data, int x);
void			init_ray_dist(t_ray *ray);
void			init_ray_step(t_ray *ray);

/* perform_dda.c */
void			perform_dda(t_ray *ray, t_data *data);
void			calculate_wall_dist(t_ray *ray);
void			calculate_line_height(t_ray *ray);

/* vectors.c */
void			set_direction_vectors(t_ray *ray, char dir);

/* key_events.c */
int				handle_keypress(int keycode, t_data *data);
int				handle_keyrelease(int keycode, t_data *data);

/* player_movement.c */
void			handle_forward_movement(t_data *data);
void			handle_strafe_movement(t_data *data);

/* player_rotation.c */
void			handle_rotation(t_data *data);
void			handle_rotation_left(t_data *data);

/* utils.c */
int				error_msg(char *msg);
void			free_split(char **split);
int				get_max_line_length(char **map);
int				check_xpm_extension(char *path);
// int				check_texture_size(void *texture1, void *texture2);
int				check_texture_size(t_texture *texture1, t_texture *texture2);

/* parse_map.c */
int				parse_map(int fd, char *first_line, t_data *data);
int				init_map(t_data *data, int fd, char *first_line);

/* texure_utils_1.c */
int				validate_textures(t_data *data);
int				get_texture_color(t_data *data, t_ray *ray, int y);
void			check_texture_paths(t_data *data);

/* texture_utils_2.c */
// int				load_all_textures(t_data *data);
void			*get_wall_texture_ptr(t_data *data, t_ray *ray);

/* errors.c */
void			error_mlx(char *message, t_data *data);
void			error_malloc(char *message, t_data *data);
void			error_texture(char *message, t_data *data);	
void			error_map(char *message, t_data *data);
void			exit_with_error(char *message, t_data *data);

/* free.c */
void			free_texture_paths(t_data *data);
void			free_textures(t_data *data);
void			free_map(t_data *data);
void			free_mlx(t_data *data);
void			free_resources(t_data *data);

/* clean.c */
// void			free_resources(t_data *data); //en attente de fusion
void			free_texture(t_data *data, t_texture **texture);
void			free_textures_bis(t_data *data);
void			free_map_array(char **map, int height);
void			free_mlx_resources(t_data *data);

/* minimap_player*/
void			draw_player_on_map(t_data *data);

/* minimap_utils */
int				get_minimap_color(char map_char);
int				is_in_minimap_bounds(t_minimap *minimap, int x, int y);
void			clear_minimap(t_data *data, t_minimap *minimap);

/* minimap.c */
void			init_minimap(t_data *data);
void			put_pixel_minimap(t_data *data, int x, int y, int color);
void			put_minimap_pixel(t_data *data, int map_x, int map_y, int color);
void			draw_map_content(t_data *data);
void			draw_minimap(t_data *data);

#endif
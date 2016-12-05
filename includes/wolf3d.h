/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 11:26:50 by tguillem          #+#    #+#             */
/*   Updated: 2016/12/05 13:35:18 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define VERSION_MAJOR 1
# define VERSION_MINOR 0
# define DIR_X -1
# define DIR_Y 0
# define CAM_X 0
# define CAM_Y 0.66
# define SPEED_MOVE 0.15
# define SPEED_ROTATE 0.05
# include "graphics.h"
# include <unistd.h>
# include <fcntl.h>
# ifdef __APPLE__
#  define ARROW_OFFSET 122
#  define ARROW_RIGHT ARROW_OFFSET + 2
#  define ARROW_DOWN ARROW_OFFSET + 3
#  define ARROW_UP ARROW_OFFSET + 4
# else
#  define ARROW_OFFSET 65360
#  define ARROW_RIGHT ARROW_OFFSET + 3
#  define ARROW_UP ARROW_OFFSET + 2
#  define ARROW_DOWN ARROW_OFFSET + 4
# endif
# define ARROW_LEFT ARROW_OFFSET + 1

typedef struct			s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				speed_move;
	double				speed_rotate;
}						t_player;

typedef struct			s_camera
{
	double				x;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				dist_wall;
}						t_camera;

typedef struct			s_draw
{
	int					x;
	int					map_x;
	int					map_y;
	int					height;
	int					start;
	int					end;
	int					color;
	int					side;
	int					hit;
	int					step_x;
	int					step_y;
	double				dist_side_x;
	double				dist_side_y;
	double				dist_delta_x;
	double				dist_delta_y;
}						t_draw;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_image				*render;
	int					update;
	int					temp_x;
	unsigned char		**map;
	unsigned char		map_x;
	unsigned char		map_y;
	unsigned short		block_size;
	unsigned char		key_down;
	unsigned char		key_up;
	unsigned char		key_left;
	unsigned char		key_right;
	t_player			*player;
	t_camera			*camera;
	t_draw				*draw;
}						t_env;

t_env					*init_data(void);
int						init_display(t_env *env);
int						destroy_env(t_env *env, int exit_code);
int						parse_header(t_env *env, int fd);
int						parse_map(t_env *env, int fd);
char					*read_fd(int fd, int size);
char					read8(int fd, unsigned char *result);
char					read16(int fd, unsigned short *result);
void					recompile_render(t_env *env);
void					process_raycasting(t_env *env);
unsigned int			get_face_color(t_env *e);
void					rotate_player_left(t_env *env);
void					rotate_player_right(t_env *env);
void					move_player_up(t_env *env);
void					move_player_down(t_env *env);
void					render_infos(t_env *env);
int						key_press(int keycode, void *param);
int						key_release(int keycode, void *param);
void					key_update(t_env *env);
int						get_pos(t_env *env, int x, int y);
#endif

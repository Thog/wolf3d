/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 11:26:50 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/28 15:48:06 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define VERSION_MAJOR 1
# define VERSION_MINOR 0
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
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
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
unsigned int			get_face_color(unsigned char type);


void					move_forward(t_env *env);
void					move_backward(t_env *env);
void					rotate_player(t_env *env, double speed);
int						getPos(t_env *env, int x, int y);
#endif

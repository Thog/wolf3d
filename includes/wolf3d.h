/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 11:26:50 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/09 16:53:35 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define VERSION_MAJOR 1
# define VERSION_MINOR 0
# include "graphics.h"
# include <unistd.h>
# include <fcntl.h>

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
	double				origin_dir_x;
	double				origin_dir_y;
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
#endif

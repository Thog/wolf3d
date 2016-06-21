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
# include "graphics.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_image				*render;
	int					update;
	unsigned char		**map;
	unsigned char		map_x;
	unsigned char		map_y;
	unsigned short		block_size;
}						t_env;

t_env					*init_data(void);
int						destroy_env(t_env *env, int exit_code);
int						parse_header(t_env *env, int fd);
int						parse_map(int fd);
char					*read_fd(int fd, int size);
char					read8(int fd, unsigned char *result);
char					read16(int fd, unsigned short *result);

#endif

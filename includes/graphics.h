/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 11:26:50 by tguillem          #+#    #+#             */
/*   Updated: 2016/07/18 16:45:16 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include <mlx.h>
# include <math.h>
# include "libft.h"
# define WIDTH 800
# define HEIGHT 600
# define ISO_C1 0.5F
# define ISO_C2 0.5F
# define PROJ_ISO_X(X, Y, Z) ISO_C1 * X - ISO_C2 * Y
# define PROJ_ISO_Y(X, Y, Z) -Z + (ISO_C1 / 2) * X + (ISO_C2 / 2) * Y
# define RGB(R, G, B) ((R & 0xFF) << 16) | ((G & 0xFF) << 8) | (B & 0xFF)
# define PURPLE 0xFF00FF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define CYAN 0x00FFFF
# define WHITE 0xFFFFFF
# define YELLOW 0xFFD800
# ifdef __APPLE__
#  define ESCAPE 53
# else
#  define ESCAPE 65307
# endif
# ifndef M_PI
#  define M_PI acos(-1)
# endif
# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)

typedef int				(*t_transformer)(int x, int y, int z);
typedef unsigned int	(*t_colorizer)(int iteration);

typedef struct			s_pos
{
	int					x;
	int					y;
	int					z;
}						t_pos;

typedef struct			s_image
{
	void				*ptr;
	char				*data;
	int					byte_per_pixel;
	int					endian;
	int					line_size;
	int					width;
	int					height;
}						t_image;

typedef struct			s_color
{
	int					red;
	int					green;
	int					blue;
	int					alpha;
}						t_color;

t_pos					*new_pos(int x, int y, int z);
t_image					*new_img(void *mlx, int width, int height);
int						put_pixel(t_image *img, int x, int y,
	unsigned int color);
void					set_pixel(t_image *img, int x, int y,
	unsigned int color);
int						draw_line_2d(t_image *img, t_pos *start, t_pos *end,
	unsigned int color);
int						draw_line_3d(t_image *img, t_pos *start, t_pos *end,
	unsigned int color);
int						expose_hook(void *param);
int						key_hook(int keycode, void *param);
int						mouse_hook(int button, int x, int y, void *param);
int						motion_hook(int x, int y, void *param);
int						loop_hook(void *param);
#endif

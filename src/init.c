#include "wolf3d.h"

int					is_valid_header(int fd)
{
	char		*header;
	int			result;

	header = read_fd(fd, 10);
	if (!header)
		return (0);
	result = !ft_memcmp(header, "WOLF3D\0\0\0", 10);
	ft_memdel((void**)&header);
	return (result);
}

int						parse_header(t_env *env, int fd)
{
	unsigned short	total_map_bytes;

	if (!is_valid_header(fd) || !read8(fd, &env->map_x)
		|| !read8(fd, &env->map_y) || !read16(fd, &env->block_size)
		|| !read16(fd, &total_map_bytes))
		return (ft_error_retint("Invalid file!\n", 1));
	return ((total_map_bytes != (env->map_x * env->map_y)) ?
		ft_error_retint("Invalid map sum\n", 1) : 0);
}

int						parse_map(t_env *env, int fd)
{
	int		x;
	int		y;
	unsigned char test;

	if(!(env->map = (unsigned char**)ft_memalloc(
		sizeof(char*) * (env->map_y + 1))))
		return (ft_error_retint("Map allocation failed!\n", 1));
	y = -1;
	while ((++y) < (env->map_y + 1))
	{
		if(!(env->map[y] = (unsigned char*)ft_memalloc(sizeof(char)
			* (env->map_x + 1))))
			return (ft_error_retint("Map line allocation failed!\n", 1));
		x = -1;
		while ((++x) < (env->map_x + 1))
		{
			if (!read8(fd, &test))
				return (ft_error_retint("Map is incorrect!\n", 1));
			env->map[y][x] = test;
			if (env->pos_x == x && env->pos_y == y)
				ft_printf("X|");
			else
				ft_printf("%d|", env->map[y][x]);
		}
		ft_printf("\n");
	}
	return (0);
}

t_env					*init_data(void)
{
	int					fd;
	int					error;
	t_env				*env;

	fd = open("basic.wolf", O_BINARY);
	if (!(env = (t_env*)ft_memalloc(sizeof(t_env))))
		error = ft_error_retint("Cannot allocate memory for env struct!\n", 1);
	if (fd == -1)
		error = ft_error_retint("File not found\n", 1);
	if (!error)
	{
		error = parse_header(env, fd);
		if(!error)
			ft_printf("xSize: %u, ySize: %u, blockSize: %u\n", env->map_x + 1,
			env->map_y + 1, env->block_size);
		env->pos_x = 14;
		env->pos_y = 8;
		env->dir_y = 1;
		env->dir_x = -1;
		env->plane_y = 0.66;
		error = error ? error : parse_map(env, fd);
	}
	close(fd);
	return (error ? NULL : env);
}

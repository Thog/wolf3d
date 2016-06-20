#include "wolf3d.h"

int			is_valid_header(int fd)
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

int			init_data(void)
{
	int					fd;
	unsigned char		x;
	unsigned char		y;
	unsigned short		block;

	fd = open("basic.wolf", O_BINARY);
	if (fd == -1)
		return (ft_error_retint("File not found\n", 1));

	if (!is_valid_header(fd) || !read8(fd, &x) || !read8(fd, &y) || !read16(fd, &block))
		return (ft_error_retint("Invalid file!\n", 1));
	ft_printf("xSize: %x, ySize: %x, blockSize: %x\n", x, y, block);
	close(fd);
	return (0);
}

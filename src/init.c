#include "wolf3d.h"

int			init_data(void)
{
	int					fd;
	unsigned char		x;
	unsigned char		y;
	unsigned short		block;

	fd = open("basic.wolf", O_BINARY);
	if (fd == -1)
		return (ft_error_retint("File not found\n", 1));

	x = read8(fd);
	y = read8(fd);
	block = read16(fd);
	ft_printf("xSize: %x, ySize: %x, blockSize: %x\n", x, y, block);
	close(fd);
	return (0);
}

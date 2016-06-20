
#include "libft.h"

int			is_le()
{
	unsigned int		x;

	x = 1;
	return ((int) (((char *)&x)[0]));
}

int			is_be()
{
	return (!is_le());
}

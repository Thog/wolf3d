/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 16:03:31 by tguillem          #+#    #+#             */
/*   Updated: 2016/06/28 16:10:36 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char					*read_fd(int fd, int size)
{
	char		*buffer;
	int			res;

	if (fd <= 0 || !(buffer = ft_memalloc(sizeof(char) * size)))
		return (NULL);
	if ((res = read(fd, buffer, size)) == size)
		return (buffer);
	return (NULL);
}

char					read8(int fd, unsigned char *result)
{
	char		*buffer;
	char		ret;

	buffer = read_fd(fd, 1);
	ret = buffer && result;
	if (result)
		*result = *buffer;
	ft_memdel((void**)&buffer);
	return (ret);
}

char					read16(int fd, unsigned short *result)
{
	char			*buffer;
	char			tmp;
	char			ret;

	if (!(buffer = read_fd(fd, 2)) || !result)
		ret = 0;
	else
	{
		if (is_le())
		{
			tmp = *buffer;
			*buffer = *(buffer + 1);
			*(buffer + 1) = tmp;
		}
		ret = 1;
		*result = *((unsigned short*)buffer);
	}
	ft_memdel((void**)&buffer);
	return (ret);
}

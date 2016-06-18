/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 08:53:41 by tguillem          #+#    #+#             */
/*   Updated: 2016/05/20 11:47:23 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *result;

	result = NULL;
	while (*s)
	{
		if (*s == c)
			result = (char*)s;
		++s;
	}
	return (!c ? (char*)s : result);
}

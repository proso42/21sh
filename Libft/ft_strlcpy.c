/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 23:19:40 by proso             #+#    #+#             */
/*   Updated: 2017/11/24 03:05:47 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

size_t	ft_strlcpy(char *dst, char const *src, size_t size)
{
	/*
	char	*dst2;
	char	*src2;
	size_t	i;

	dst2 = dst;
	src2 = (char*)src;
	i = size;
	if (i > 1)
	{
		while (--i)
		{
			*dst2 = *src2;
			dst2++;
			src2++;
		}
	}
	if (i == 0 || i == 1)
	{
		if (size)
			*dst2 = '\0';
		while (*src2)
			src2++;
	}
	return (src2 - src - 1);
	*/
	ft_strncpy(dst, src, size);
	dst[size] = '\0';
	return (ft_strlen(src));
}

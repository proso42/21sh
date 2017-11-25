/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 00:38:18 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 00:39:53 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

char	*ft_realloc(char *str, int size)
{
	char	*tmp;

	tmp = ft_strnew(size * 2);
	ft_strcpy(tmp, str);
	ft_strdel(&str);
	return (tmp);
}

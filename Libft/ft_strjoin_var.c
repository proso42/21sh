/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 23:38:18 by proso             #+#    #+#             */
/*   Updated: 2017/11/16 00:38:37 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

char		*ft_strjoin_var(int nb, ...)
{
	va_list	ap;
	char	*join;
	char	*tmp;
	int		size;
	int		i;

	if (nb <= 0)
		return (NULL);
	i = nb;
	size = 0;
	va_start(ap, nb);
	while (i > 0)
	{
		tmp = va_arg(ap, char*);
		size += ft_strlen(tmp);
		i--;
	}
	va_end(ap);
	va_start(ap, nb);
	join = ft_strnew(size);
	while (nb > 0)
	{
		tmp = va_arg(ap, char*);
		ft_strcat(join, tmp);
		nb--;
	}
	va_end(ap);
	return (ft_strdup(join));
}

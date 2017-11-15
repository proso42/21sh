/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 23:38:18 by proso             #+#    #+#             */
/*   Updated: 2017/11/13 23:42:30 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

char	*ft_strjoin_var(int nb, ...)
{
	va_list	ap;
	char	join[1024];
	char	*tmp;

	if (nb <= 0)
		return (NULL);
	va_start(ap, nb);
	ft_bzero(join, 1024);
	while (nb > 0)
	{
		tmp = va_arg(ap, char*);
		ft_strcat(join, tmp);
		nb--;
	}
	va_end(ap);
	return (ft_strdup(join));
}

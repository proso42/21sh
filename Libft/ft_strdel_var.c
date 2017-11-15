/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 23:48:36 by proso             #+#    #+#             */
/*   Updated: 2017/11/13 23:50:27 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void	ft_strdel_var(int nb, ...)
{
	va_list	ap;
	char	**str;

	if (nb <= 0)
		return ;
	va_start(ap, nb);
	while (nb > 0)
	{
		str = va_arg(ap, char**);
		ft_strdel(str);
		nb--;
	}
	va_end(ap);
}

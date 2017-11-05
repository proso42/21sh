/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 02:41:13 by proso             #+#    #+#             */
/*   Updated: 2017/11/05 02:43:06 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	ft_inc(int inc, int nb, ...)
{
	va_list	ap;
	int		*val;

	va_start(ap, nb);
	while (nb > 0)
	{
		val = va_arg(ap, int*);
		*val += inc;
		nb--;
	}
	va_end(ap);
}

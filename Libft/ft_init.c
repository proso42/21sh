/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variable_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 13:47:52 by proso             #+#    #+#             */
/*   Updated: 2017/06/19 13:48:00 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void	ft_init(int x, int nb, ...)
{
	va_list	ap;
	int		*val;

	va_start(ap, nb);
	while (nb > 0)
	{
		val = va_arg(ap, int*);
		*val = x;
		nb--;
	}
	va_end(ap);
}

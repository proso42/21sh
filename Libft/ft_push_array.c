/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 02:03:00 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 02:30:44 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void	ft_push_array(char **array, char *str, size_t size)
{
	int		i;

	if (!array || !str)
		return ;
	i = 0;
	while (array[i][0] && i < (int)size)
		i++;
	ft_strlcpy(array[i], str, 1024);
}

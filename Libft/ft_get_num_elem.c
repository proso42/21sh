/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_num_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:47:16 by proso             #+#    #+#             */
/*   Updated: 2017/09/13 13:55:36 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

int		ft_get_num_elem(t_list *begin_list, char *str)
{
	int		i;
	t_list	*current;

	i = 0;
	current = begin_list;
	if (!current || !current->data)
		return (-1);
	while (ft_strcmp(str, current->data) && current)
	{
		current = current->next;
		if (!current)
			return (-1);
		i++;
	}
	return (i);
}

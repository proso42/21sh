/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 20:29:05 by proso             #+#    #+#             */
/*   Updated: 2017/05/15 11:58:56 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

t_list		**ft_get_addr_elem(t_list **begin_list, int i)
{
	t_list	*current;
	t_list	**addr;

	if (!*begin_list || i < 0)
		return (NULL);
	current = *begin_list;
	while (i > 0)
	{
		i--;
		if (current->next)
			current = current->next;
		else
			return (NULL);
	}
	addr = &current;
	return (addr);
}

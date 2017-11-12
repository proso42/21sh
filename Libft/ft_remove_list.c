/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 22:15:15 by proso             #+#    #+#             */
/*   Updated: 2017/11/10 02:51:07 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void	ft_remove_list(t_list **begin_list)
{
	t_list	*previous;

	while (*begin_list)
	{
		ft_strdel((char**)&(*begin_list)->data);
		previous = *begin_list;
		*begin_list = previous->next;
		free(previous);
	}
	*begin_list = NULL;
}

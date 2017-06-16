/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 23:22:25 by proso             #+#    #+#             */
/*   Updated: 2017/05/06 23:22:27 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

t_list	*ft_tab_to_list(char **av)
{
	t_list	*list;
	int		i;

	i = 0;
	list = NULL;
	if (!av || !*av)
		return (NULL);
	while (av[i])
	{
		if (!(ft_push_back(&list, av[i])))
			return (NULL);
		i++;
	}
	return (list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 19:09:45 by proso             #+#    #+#             */
/*   Updated: 2017/06/03 19:10:00 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	t_btree	*current;

	current = root;
	if (current)
	{
		if (current->left)
		{
			btree_apply_infix(current->left, applyf);
			applyf(current->item);
		}
		else
			applyf(current->item);
		if (current->right)
			btree_apply_infix(current->right, applyf);
	}
}

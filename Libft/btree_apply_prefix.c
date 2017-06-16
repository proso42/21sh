/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 18:52:50 by proso             #+#    #+#             */
/*   Updated: 2017/06/03 18:52:59 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void	btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	t_btree	*current;

	current = root;
	if (current)
	{
		applyf(current->item);
		if (current->left)
			btree_apply_prefix(current->left, applyf);
		if (current->right)
			btree_apply_prefix(current->right, applyf);
	}
}

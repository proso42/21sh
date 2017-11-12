/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_sufix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 19:12:22 by proso             #+#    #+#             */
/*   Updated: 2017/11/09 23:14:04 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void	btree_apply_sufix(t_btree *root, void (*applyf)(void *))
{
	t_btree	*current;

	current = root;
	if (current)
	{
		if (current->left)
			btree_apply_sufix(current->left, applyf);
		if (current->right)
			btree_apply_sufix(current->right, applyf);
		applyf(current->item);
	}
}

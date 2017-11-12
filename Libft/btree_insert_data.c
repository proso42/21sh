/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 19:21:25 by proso             #+#    #+#             */
/*   Updated: 2017/11/10 03:12:31 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void	btree_insert_data(t_btree **root, void *item, int (*f)(void *, void *))
{
	t_btree	*node;
	t_btree	*current;
	int		rep;

	current = *root;
	if (current)
	{
		node = btree_create_node(item);
		while (current->left != node && current->right != node)
		{
			rep = f(current->item, node->item);
			if (rep >= 0 && !current->left)
				current->left = node;
			else if (rep >= 0 && current->left)
				current = current->left;
			else if (rep < 0 && !current->right)
				current->right = node;
			else if (rep < 0 && current->right)
				current = current->right;
		}
	}
	else
		*root = btree_create_node(item);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 22:29:21 by proso             #+#    #+#             */
/*   Updated: 2017/06/03 22:29:23 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void	*btree_search_item(t_btree *root, void *ref, int (*f)(void *, void *))
{
	t_btree	*current;
	t_btree	*search;

	current = root;
	if (!current || !ref)
		return (NULL);
	if (!(f(root->item, ref)))
		return (root->item);
	if (current->left)
		if ((search = btree_search_item(current->left, ref, f)))
			return (search);
	if (current->right)
		if ((search = btree_search_item(current->right, ref, f)))
			return (search);
	return (NULL);
}

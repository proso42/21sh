/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_remove_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 01:37:46 by proso             #+#    #+#             */
/*   Updated: 2017/11/11 22:55:29 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void		btree_remove_all(t_btree **root, void (*del)(void *))
{
	if (!(*root))
		return;
	if ((*root)->left != NULL)
		btree_remove_all(&((*root)->left), del);
	if ((*root)->right != NULL)
		btree_remove_all(&((*root)->right), del);
	del((*root)->item);
	free(*root);
	*root = NULL;
}

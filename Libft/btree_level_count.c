/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 15:26:47 by proso             #+#    #+#             */
/*   Updated: 2017/06/04 15:26:49 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

int		level_count_rec(t_btree *root, int *i, int *i_max)
{
	if (root->left)
	{
		(*i)++;
		*i_max = (*i > *i_max) ? *i : *i_max;
		level_count_rec(root->left, i, i_max);
		(*i)--;
	}
	if (root->right)
	{
		(*i)++;
		*i_max = (*i > *i_max) ? *i : *i_max;
		level_count_rec(root->right, i, i_max);
		(*i)--;
	}
	return (*i_max);
}

int		btree_level_count(t_btree *root)
{
	int		i;
	int		i_max;

	i = 0;
	i_max = 0;
	return ((!root) ? 0 : level_count_rec(root, &i, &i_max));
}

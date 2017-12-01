/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lexem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 00:07:54 by proso             #+#    #+#             */
/*   Updated: 2017/11/30 01:24:30 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"
#define DATA ((t_lexem*)current->data)

int		only_space(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	clean_lexem(t_data *info)
{
	t_list	*current;
	int		i;

	if (info->tmp_buf)
		ft_strdel(&info->tmp_buf);
	current = info->lexem_list;
	while (current)
	{
		i = 0;
		while (DATA->cmd && DATA->cmd[i] && DATA->cmd[i][0])
		{
			replace_dollard(info, &DATA->cmd[i]);
			replace_tild(info, &DATA->cmd[i]);
			remove_useless_symbol(&DATA->cmd[i]);
			i++;
		}
		current = current->next;
	}
	info->quote = 0;
}

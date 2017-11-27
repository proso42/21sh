/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 21:43:31 by proso             #+#    #+#             */
/*   Updated: 2017/11/27 01:37:14 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	end_of_line(t_data *info)
{
	if (!info->buf_cmd[0] && !info->quote)
		default_terminal(info, -1);
	else if (!info->buf_cmd[0] && info->quote)
	{
		term_action(info, "do");
		ft_printf("{red}{bold}21sh: syntax error: unexpected EOF{res}\n");
		ft_strdel(&info->save_buf);
		info->quote = 0;
		print_prompt(info);
		ft_strdel(&info->buf_cmd);
		info->size_max = 1024;
		info->buf_cmd = ft_strnew(info->size_max);
		info->buf_i = 0;
		btree_remove_all(&info->root, del);
		ft_remove_list(&info->lexem_list);
	}
}

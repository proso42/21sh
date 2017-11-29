/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 00:54:45 by proso             #+#    #+#             */
/*   Updated: 2017/11/29 01:59:40 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	event_tab_history(t_data *info)
{
	char	*tmp;
	int		size;

	size = info->sz.ws_col;
	if (info->hist->pos_list < 0)
		return ;
	ft_strncpy(info->hist->search, ft_get_elem(info->hist->match_list,
								info->hist->pos_list), info->sz.ws_col - 10);
	term_tgoto(info, 0, 0);
	clear_history_lines(info);
	term_tgoto(info, 0, 0);
	ft_remove_list(&info->hist->match_list);
	get_match_data(info, info->hist->search);
	print_correct_history(info);
	info->hist->too_long = 0;
	term_tgoto(info, 0, 0);
	if ((int)ft_strlen(info->hist->search) >= size - 10)
	{
		tmp = ft_strdup(info->hist->search);
		tmp[size - 10] = '\0';
		tmp[size - 11] = '.';
		tmp[size - 12] = '.';
		tmp[size - 13] = '.';
		ft_printf("{bold}{blue}search : {res}%s", tmp);
		ft_strdel(&tmp);
		info->hist->too_long = 1;
	}
	else
		ft_printf("{bold}{blue}search : {res}%s", info->hist->search);
}

int				event_enter_history(t_data *info)
{
	char	*s;

	term_action(info, "te");
	del_line(info);
	info->buf_i = 0;
	ft_bzero(info->buf_cmd, info->size_max);
	if (info->prompt_size >= info->sz.ws_col)
		info->curs_x = (info->prompt_size - info->sz.ws_col);
	else
		info->curs_x = info->prompt_size;
	info->curs_y = 0;
	if (info->hist->pos_list > -1)
		s = ft_get_elem(info->hist->match_list, info->hist->pos_list);
	else
		s = info->hist->search;
	ft_strlcpy(info->buf_cmd, s, info->size_max);
	info->buf_i = ft_strlen(info->buf_cmd);
	write_buf(info);
	info->searching = 0;
	term_action(info, "ve");
	ft_remove_list(&info->hist->match_list);
	return (2);
}

void			event_letter_history(t_data *info)
{
	if ((int)ft_strlen(info->hist->search) + 9 >= info->sz.ws_col - 1)
		return ;
	ft_remove_list(&info->hist->match_list);
	ft_strcat(info->hist->search, info->hist->key);
	term_tgoto(info, 0, 0);
	ft_printf("{bold}{blue}search : {res}%s", info->hist->search);
	get_match_data(info, info->hist->search);
	clear_history_lines(info);
	print_correct_history(info);
	term_tgoto(info, ft_strlen(info->hist->search) + 9, 0);
}

void			event_delete_history(t_data *info)
{
	int		x;

	x = ft_strlen(info->hist->search);
	if (info->hist->too_long)
	{
		term_action(info, "le");
		term_action(info, "dc");
		term_action(info, "le");
		term_action(info, "dc");
		term_action(info, "le");
		term_action(info, "dc");
		write(0, &info->hist->search[x - 2], 2);
	}
	info->hist->search[x - 1] = '\0';
	term_tgoto(info, 0, 0);
	clear_history_lines(info);
	term_tgoto(info, x + 8, 0);
	term_action(info, "dc");
	ft_remove_list(&info->hist->match_list);
	get_match_data(info, info->hist->search);
	print_correct_history(info);
	term_tgoto(info, ft_strlen(info->hist->search) + 9, 0);
}

void			event_cursor_history(t_data *info)
{
	t_list	*current;
	int		j;

	current = info->hist->match_list;
	if (!current)
	{
		info->hist->pos_list = -1;
		return ;
	}
	j = 0;
	if (info->hist->pos_list <= 0 && info->hist->key[2] == 65)
		info->hist->pos_list = ft_list_size(info->hist->match_list) - 1;
	else if (info->hist->pos_list >= (ft_list_size(info->hist->match_list) - 1)
													&& info->hist->key[2] == 66)
		info->hist->pos_list = 0;
	else
		(info->hist->key[2] == 65) ? info->hist->pos_list-- :
														info->hist->pos_list++;
	term_action(info, "do");
	while (current)
	{
		if (info->hist->pos_list == j)
			ft_printf("{magenta}%s{res}", current->data);
		else
			ft_putstr(current->data);
		term_action(info, "do");
		current = current->next;
		j++;
	}
	term_tgoto(info, ft_strlen(info->hist->search) + 9, 0);
}

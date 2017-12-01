/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_history2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 01:28:58 by proso             #+#    #+#             */
/*   Updated: 2017/12/01 01:12:52 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void	search_too_long(t_data *info, int size)
{
	char	*tmp;

	tmp = ft_strdup(info->hist->search);
	tmp[size - 10] = '\0';
	tmp[size - 11] = '.';
	tmp[size - 12] = '.';
	tmp[size - 13] = '.';
	ft_printf("{bold}{blue}search : {res}%s", tmp);
	ft_strdel(&tmp);
	info->hist->too_long = 1;
}

void		event_tab_history(t_data *info)
{
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
		search_too_long(info, size);
	else
		ft_printf("{bold}{blue}search : {res}%s", info->hist->search);
}

void		print_correct_history(t_data *info)
{
	t_list	*current;
	char	*tmp;
	int		size;

	info->hist->nb_line = 0;
	size = info->sz.ws_col;
	term_action(info, "do");
	current = info->hist->match_list;
	while (current)
	{
		if ((int)ft_strlen(current->data) >= size - 1)
		{
			tmp = ft_strdup(current->data);
			tmp[size] = '\0';
			tmp[size - 1] = '.';
			tmp[size - 2] = '.';
			tmp[size - 3] = '.';
			ft_strcpy(current->data, tmp);
			ft_strdel(&tmp);
		}
		ft_putendl(current->data);
		info->hist->nb_line++;
		current = current->next;
	}
	term_action(info, "ve");
}

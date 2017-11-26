/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 00:15:19 by proso             #+#    #+#             */
/*   Updated: 2017/11/26 23:20:54 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	get_match_data(t_data *info, char *search)
{
	t_list	*current;

	current = info->history_list;
	while (current)
	{
		if (ft_strnstr(current->data, search, (int)ft_strlen(search)) &&
						!ft_list_find(info->hist->match_list, current ->data))
			ft_push_back(&info->hist->match_list, ft_strdup(current->data));
		current = current->next;
	}
}

void	print_correct_history(t_data *info)
{
	t_list	*current;
	int		size;

	info->hist->nb_line = 0;
	size = (int)ft_strlen(info->hist->search);
	term_action(info, "do");
	current = info->hist->match_list;
	while (current)
	{
		ft_putendl(current->data);
		info->hist->nb_line++;
		current = current->next;
	}
	term_action(info, "ve");
}

void	clear_history_lines(t_data *info)
{
	term_action(info, "vi");
	term_action(info, "do");
	while (info->hist->nb_line > 0)
	{
		term_action(info, "dl");
		info->hist->nb_line--;
	}
	term_tgoto(info, 0, 0);
}

static int	get_entry(t_data *info)
{
	while (1)
	{
		if (!info->hist->search[0])
		{
			term_action(info, "cl");
			ft_printf("{bold}{blue}search : {res}");
		}
		ft_bzero(info->hist->key, 6);
		read(0, info->hist->key, 6);
		if (!info->searching)
			return (2);
		if (info->hist->key[0] == 10 && !info->hist->key[1])
			return (event_enter_history(info));
		else if (info->hist->key[0] == 9 && info->hist->pos_list > -1)
			event_tab_history(info);
		else if (ft_isprint(info->hist->key[0]))
			event_letter_history(info);
		else if (info->hist->key[0] == 127 && !info->hist->key[1] &&
														info->hist->search[0])
			event_delete_history(info);
		else if (info->hist->key[0] == 27 && info->hist->key[1] == 91 &&
						(info->hist->key[2] == 65 || info->hist->key[2] == 66)
						 						&& info->hist->search[0])
			event_cursor_history(info);
		if (info->hist->key[0] != 27 || info->hist->key[1] != 91 ||
							info->hist->key[2] < 65 || info->hist->key[2] > 66)
			info->hist->pos_list = -1;

	}
	info->searching = 0;
	return (2);
}

int			history_search(t_data *info)
{
	info->hist->nb_line = 0;
	info->hist->pos_list = -1;
	ft_bzero(info->hist->search, info->size_max);
	info->hist->match_list = NULL;
	if (!info->history_list || !info->history_list->data)
		return (print_error(EMPTY_HIST));
	info->searching = 1;
	term_action(info, "ti");
	return (get_entry(info));
}

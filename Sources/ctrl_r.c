/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 00:15:19 by proso             #+#    #+#             */
/*   Updated: 2017/11/15 23:00:33 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int	print_correct_history(t_data *info, char *search)
{
	t_list	*current;
	int		nb_line;
	int		size;

	nb_line = 0;
	size = (int)ft_strlen(search);
	term_action(info, "do");
	current = info->history_list;
	while (current)
	{
		if (ft_strnstr(current->data, search, size))
		{
			ft_putendl(current->data);
			nb_line++;
		}
		current = current->next;
	}
	term_action(info, "ve");
	return (nb_line);
}

static void	clear_lines(t_data *info, int nb_line)
{
	term_action(info, "vi");
	term_action(info, "do");
	while (nb_line > 0)
	{
		term_action(info, "dl");
		nb_line--;
	}
	term_tgoto(info, 0, 0);
}

int	ctrl_r(t_data *info)
{
	char	search[1024];
	char	key[6];
	int		nb_line;

	if (!info->history_list || !info->history_list->data)
		return (print_error(EMPTY_HIST));
	info->ctrl_r = 1;
	ft_bzero(search, 1024);
	term_action(info, "ti");
	nb_line = 0;
	while (1)
	{
		if (!search[0])
		{
			term_action(info, "cl");
			ft_printf("{bold}{blue}search : {res}");
		}
		ft_bzero(key, 6);
		read(0, key, 1);
		if (key[0] == 10 && !key[1])
		{
			term_action(info, "te");
			return (get_stdin(info));
		}
		else if (ft_isprint(key[0]))
		{
			ft_strcat(search, key);
			term_tgoto(info, 0, 0);
			ft_printf("{bold}{blue}search : {res}%s", search);
			clear_lines(info, nb_line);
			nb_line = print_correct_history(info, search);
			term_tgoto(info, ft_strlen(search) + 9, 0);
		}
		else if (key[0] == 127 && !key[1])
		{
			search[ft_strlen(search) - 1] = '\0';
			term_tgoto(info, 0, 0);
			clear_lines(info, nb_line);
			term_action(info, "dl");
			ft_printf("{bold}{blue}search : {res}%s", search);
			nb_line = print_correct_history(info, search);
			term_tgoto(info, ft_strlen(search) + 9, 0);
		}
	}
	return (get_stdin(info));
}

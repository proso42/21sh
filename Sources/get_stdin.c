/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stdin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:37:25 by proso             #+#    #+#             */
/*   Updated: 2017/11/26 21:49:28 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void		choice_alt(t_data *info, char *key)
{
	if (key[3] == 67 && !key[4])
		move_next_word(info);
	else if (key[3] == 68 && !key[4])
		move_prev_word(info);
	else if (key[3] == 65 && !key[4])
		move_up(info);
	else if (key[3] == 66 && !key[4])
		move_down(info);
}

static int	suite(t_data *info, char *key)
{
	if (key[0] == 27 && key[1] == 91 && key[2] == 51 && key[3] == 126
																	&& !key[4])
		delete_right(info);
	else if (key[0] == 127 && !key[1])
		delete_left(info);
	else if (key[0] == 12 && !key[1])
		clear_sc(info);
	else if (key[0] == -61 && key[1] == -89 && !key[2])
		cpy_mode(info);
	else if (key[0] == -30 && key[1] == -119 && key[2] == -120 && !key[3])
		cut_mode(info);
	else if (key[0] == -30 && key[1] == -120 && key[2] == -102 && !key[3])
		past_mode(info);
	else if (key[0] == 18 && !key[1])
		return (history_search(info));
	else if (key[0] == 4)
		end_of_line(info);
	return (1);
}

int			get_stdin(t_data *info)
{
	char	key[6];

	ft_bzero(key, 6);
	read(0, key, 6);
	if (info->pid == -4)
		return (54);
	else if (key[0] >= ' ' && key[0] <= '~' && !key[1])
		add_to_buf(info, key);
	else if (key[0] == 27 && key[1] == 91 && (key[2] == 68 || key[2] == 67)
																	&& !key[3])
		line_edition(info, key);
	else if (key[0] == 27 && key[1] == 91 && (key[2] == 65 || key[2] == 66)
													&& !key[3] && !info->quote)
		return (get_history(info, key));
	else if (key[0] == 27 && key[1] == 91 && key[2] == 72 && !key[3])
		home(info, 1);
	else if (key[0] == 27 && key[1] == 91 && key[2] == 70 && !key[3])
		end(info);
	else if (key[0] == 27 && key[1] == 27 && key[2] == 91 && key[3])
		choice_alt(info, key);
	else if (key[0] == 10 && !key[1])
		return (test_quote(info));
	else
		return (suite(info, key));
	return (1);
}

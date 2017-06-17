/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:43:43 by proso             #+#    #+#             */
/*   Updated: 2017/06/16 15:43:45 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	move_right(t_data *info)
{
	if (info->curs_x + 1 >= info->sz.ws_col)
	{
		info->curs_x = 0;
		info->curs_y++;
		info->buf_i++;
		term_action(info, "do");
	}
	else if (info->buf_i + 1 <= (int)ft_strlen(info->buf_cmd))
	{
		info->curs_x++;
		info->buf_i++;
		term_action(info, "nd");
	}
}

void	move_left(t_data *info)
{
	if ((info->curs_y == 0 && info->curs_x - 1 >= info->prompt_size) || (
										info->curs_y > 0 && info->curs_x > 0))
	{
		info->curs_x--;
		info->buf_i--;
		term_action(info, "le");
	}
	else if (info->curs_y > 0 && info->curs_x == 0)
	{
		info->curs_y--;
		term_action(info, "up");
		while (info->curs_x + 1 < info->sz.ws_col)
		{
			term_action(info, "nd");
			info->curs_x++;
		}
		info->buf_i--;
	}
}

int		line_edition(t_data *info, char *key)
{
	if (key[2] == 68)
		move_left(info);
	else if (key[2] == 67)
		move_right(info);
	return (1);
}

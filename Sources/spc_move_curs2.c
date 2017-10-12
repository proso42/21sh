/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spc_move_curs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 21:14:55 by proso             #+#    #+#             */
/*   Updated: 2017/07/20 21:14:56 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	move_up(t_data *info)
{
	if (info->curs_y >= 1 && info->buf_i - info->sz.ws_col >= 0)
	{
		info->curs_y--;
		info->buf_i -= info->sz.ws_col;
		term_action(info, "up");
	}
	else if (info->curs_y == 1 && info->buf_i - info->sz.ws_col < 0)
			home(info, 1);
}

void	move_down(t_data *info)
{
	int		x;

	if (info->buf_i + info->sz.ws_col <= (int)ft_strlen(info->buf_cmd))
	{
		x = info->buf_i + (info->sz.ws_col - info->curs_x);
		term_action(info, "do");
		info->curs_x = 0;
		info->curs_y++;
		info->buf_i += info->sz.ws_col;
		while (x != info->buf_i)
		{
			x++;
			info->curs_x++;
			term_action(info, "nd");
		}
	}
	else
		end(info);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spc_move_curs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 17:41:48 by proso             #+#    #+#             */
/*   Updated: 2017/11/04 03:11:49 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	move_prev_word(t_data *info)
{
	while (info->buf_cmd[info->buf_i] != ' ' && info->buf_i)
		move_left(info);
	while (info->buf_cmd[info->buf_i] == ' ' && info->buf_i)
		move_left(info);
}

void	move_next_word(t_data *info)
{
	while (info->buf_cmd[info->buf_i] != ' ' && info->buf_cmd[info->buf_i])
		move_right(info);
	while (info->buf_cmd[info->buf_i] == ' ' && info->buf_cmd[info->buf_i])
		move_right(info);
}

void	home(t_data *info, int mode)
{
	term_action(info, "vi");
	while (info->curs_y > 0)
	{
		term_action(info, "up");
		info->curs_y--;
	}
	while (info->curs_x > info->prompt_size)
	{
		info->curs_x--;
		term_action(info, "le");
	}
	while (info->curs_x < info->prompt_size)
	{
		info->curs_x++;
		term_action(info, "nd");
	}
	term_action(info, "ve");
	if (mode)
		info->buf_i = 0;
}

void	end(t_data *info)
{
	term_action(info, "vi");
	while (info->buf_cmd[info->buf_i])
	{
		if (info->curs_x + 1 == info->sz.ws_col)
		{
			info->curs_x = 0;
			info->curs_y++;
			term_action(info, "do");
		}
		else
		{
			info->curs_x++;
			term_action(info, "nd");
		}
		info->buf_i++;
	}
	term_action(info, "ve");
}

void	go_good_place(t_data *info)
{
	int x;

	term_action(info, "vi");
	x = info->prompt_size;
	while (x < info->buf_i + info->prompt_size)
	{
		if (info->curs_x + 1 == info->sz.ws_col)
		{
			info->curs_x = 0;
			info->curs_y++;
			term_action(info, "do");
		}
		else
		{
			info->curs_x++;
			term_action(info, "nd");
		}
		x++;
	}
	term_action(info, "ve");
}

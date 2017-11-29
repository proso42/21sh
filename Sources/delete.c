/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 18:02:58 by proso             #+#    #+#             */
/*   Updated: 2017/11/29 23:48:20 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	del_line(t_data *info)
{
	int		i;
	int		save;

	i = info->buf_i;
	save = i;
	end(info);
	while (i >= 0)
	{
		move_left(info);
		term_action(info, "dc");
		term_action(info, "dc");
		i--;
	}
	info->buf_i = save;
}

void	delete_left(t_data *info)
{
	int		i;

	i = info->buf_i;
	if (i > 0)
	{
		move_left(info);
		ft_strncpy(&info->buf_cmd[i - 1], &info->buf_cmd[i],
															info->size_max - i);
		info->buf_cmd[ft_strlen(info->buf_cmd)] = '\0';
		del_line(info);
		home(info, 0);
		write_buf(info);
		home(info, 0);
		go_good_place(info);
	}
}

void	delete_right(t_data *info)
{
	int		i;

	i = info->buf_i;
	if (i <= (int)ft_strlen(info->buf_cmd))
	{
		ft_strncpy(&info->buf_cmd[i], &info->buf_cmd[i + 1],
															info->size_max - i);
		del_line(info);
		home(info, 0);
		write_buf(info);
		home(info, 0);
		go_good_place(info);
	}
}

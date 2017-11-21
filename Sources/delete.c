/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 18:02:58 by proso             #+#    #+#             */
/*   Updated: 2017/11/21 03:26:59 by proso            ###   ########.fr       */
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
		term_action(info, "dc");
		move_left(info);
		i--;
	}
	info->buf_i = save;
}

void	delete_left(t_data *info)
{
	char	tmp[1024];

	if (info->buf_i > 0)
	{
		ft_bzero(tmp, 1024);
		move_left(info);
		ft_strncpy(tmp, info->buf_cmd, info->buf_i);
		ft_strcat(tmp, &info->buf_cmd[info->buf_i + 1]);
		ft_bzero(info->buf_cmd, 1024);
		ft_strlcpy(info->buf_cmd, tmp, 1024);
		del_line(info);
		home(info, 0);
		write_buf(info);
		home(info, 0);
		go_good_place(info);
	}
}

void	delete_right(t_data *info)
{
	char	tmp[1024];

	if (info->buf_i <= (int)ft_strlen(info->buf_cmd))
	{
		ft_bzero(tmp, 1024);
		ft_strncpy(tmp, info->buf_cmd, info->buf_i);
		ft_strcat(tmp, &info->buf_cmd[info->buf_i + 1]);
		ft_bzero(info->buf_cmd, 1024);
		ft_strlcpy(info->buf_cmd, tmp, 1024);
		del_line(info);
		home(info, 0);
		write_buf(info);
		home(info, 0);
		go_good_place(info);
	}
}

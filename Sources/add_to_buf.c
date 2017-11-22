/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_buf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:51:38 by proso             #+#    #+#             */
/*   Updated: 2017/11/22 02:39:01 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	write_buf(t_data *info)
{
	int		i;

	i = 0;
	while (info->buf_cmd[i])
	{
		ft_putchar(info->buf_cmd[i]);
		i++;
		if (info->curs_x + 1 == info->sz.ws_col)
		{
			info->curs_x = 0;
			info->curs_y++;
			term_action(info, "do");
		}
		else
			info->curs_x++;
	}
}

int		edit_buf(t_data *info, char *key)
{
	char	tmp[1024];

	ft_bzero(tmp, 1024);
	ft_strncpy(tmp, info->buf_cmd, info->buf_i);
	tmp[info->buf_i] = key[0];
	ft_strncpy(&tmp[info->buf_i + 1], &info->buf_cmd[info->buf_i], 1024);
	ft_bzero(info->buf_cmd, 1024);
	ft_strlcpy(info->buf_cmd, tmp, 1024);
	home(info, 0);
	write_buf(info);
	info->buf_i++;
	home(info, 0);
	go_good_place(info);
	return (1);
}

int		add_to_buf(t_data *info, char *key)
{
	if ((int)ft_strlen(info->buf_cmd) == 1023)
		return (0);
	if (info->buf_i != (int)ft_strlen(info->buf_cmd))
		return (edit_buf(info, key));
	info->buf_cmd[info->buf_i] = key[0];
	info->buf_i++;
	ft_putchar(key[0]);
	if (info->curs_x + 1 == info->sz.ws_col)
	{
		info->curs_x = 0;
		info->curs_y++;
		term_action(info, "do");
	}
	else
		info->curs_x++;
	return (0);
}

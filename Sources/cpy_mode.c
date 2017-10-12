/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 23:16:34 by proso             #+#    #+#             */
/*   Updated: 2017/07/20 23:16:36 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void		replace_curs(t_data *info)
{
	int		i;

	if (!(info->curs_x == info->sz.ws_col - 1))
		term_action(info, "le");
	else
	{
		i = 0;
		while (i < info->sz.ws_col)
		{
			term_action(info, "nd");
			i++;
		}
	}
}

static void		get_arrow(t_data *info)
{
	char	key[4];
	int		min;
	int		max;

	min = info->buf_i;
	max = info->buf_i;
	while (info->cpy == NULL)
	{
		ft_bzero(key, 4);
		read(0, key, 4);
		if (key[0] == 27 && key[1] == 91 && (key[2] == 68 || key[2] == 67)
																	&& !key[3])
		{
			line_edition(info, key);
			if (info->buf_cmd[info->buf_i])
			{
				ft_printf("{bold}{green}%c{res}", info->buf_cmd[info->buf_i]);
				replace_curs(info);
				min = (info->buf_i < min) ? info->buf_i : min;
				max = (info->buf_i >= max) ? info->buf_i : max;
			}
		}
		else if (key[0] == 10 && !key[1])
			info->cpy = ft_strsub(info->buf_cmd, min, max - min + 1);
	}
}

int				cpy_mode(t_data *info)
{
	if ((info->cpy != NULL))
		ft_strdel(&info->cpy);
	if (info->buf_cmd[info->buf_i])
	{
		ft_printf("{bold}{green}%c{res}", info->buf_cmd[info->buf_i]);
		replace_curs(info);
	}
	get_arrow(info);
	home(info, 1);
	info->curs_y = 0;
	info->curs_x = info->prompt_size;
	write_buf(info);
	info->buf_i = (int)ft_strlen(info->buf_cmd);
	return (1);
}

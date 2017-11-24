/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:58:13 by proso             #+#    #+#             */
/*   Updated: 2017/11/24 23:46:12 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void	push_history(t_data *info)
{
	char *str;

	if (info->buf_cmd[0])
	{
		str = ft_strdup(info->buf_cmd);
		ft_push_back(&info->history_list, str);
	}
}

void		add_cmd_to_history(t_data *info)
{
	int		i;
	int		j;

	ft_init(0, 2, &i, &j);
	if (info->buf_cmd[0])
		push_history(info);
	else if (info->av[0][0])
	{
		while (info->av[i][0] && info->av[i][j] != '\n')
		{
			while (info->av[i][j] && info->av[i][j] != '\n')
				j++;
			if (!info->av[i][j])
			{
				ft_strcat(info->buf_cmd, info->av[i]);
				info->buf_cmd[ft_strlen(info->buf_cmd)] = ' ';
			}
			else
				ft_strncat(info->buf_cmd, info->av[i], j);
			i++;
			j = 0;
		}
		push_history(info);
	}
}

static void	show_history(t_data *info, int max_history_list)
{
	char	*str;

	info->buf_i = ft_strlen(info->buf_cmd);
	str = ft_get_elem(info->history_list, max_history_list - info->num_history);
	del_line(info);
	ft_bzero(info->buf_cmd, 1024);
	ft_strlcpy(info->buf_cmd, str, 1024);
	write_buf(info);
	info->buf_i = ft_strlen(info->buf_cmd);
}

static void	show_current(t_data *info)
{
	info->buf_i = ft_strlen(info->buf_cmd);
	del_line(info);
	ft_bzero(info->buf_cmd, 1024);
	ft_strlcpy(info->buf_cmd, info->tmp_buf, 1024);
	write_buf(info);
	info->buf_i = ft_strlen(info->buf_cmd);
	ft_bzero(info->tmp_buf, 1024);
}

int			get_history(t_data *info, char *key)
{
	int		max_history_list;

	if (!info->tmp_buf)
		info->tmp_buf = ft_strnew(1024);
	max_history_list = ft_list_size(info->history_list) - 1;
	if (info->num_history == -1)
		ft_strlcpy(info->tmp_buf, info->buf_cmd, 1024);
	info->num_history += (key[2] == 65) ? 1 : -1;
	info->num_history = (key[2] == 66 && info->num_history > max_history_list) ?
									max_history_list - 1 : info->num_history;
	if (!(info->num_history < 0 || info->num_history > max_history_list))
		show_history(info, max_history_list);
	else if (info->num_history == -1)
		show_current(info);
	if (info->num_history < -1)
		info->num_history = -1;
	else if (info->num_history > max_history_list)
		info->num_history = max_history_list;
	ft_strdel(&info->tmp_buf);
	return (2);
}

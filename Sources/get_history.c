/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:58:13 by proso             #+#    #+#             */
/*   Updated: 2017/11/29 23:28:55 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void		add_cmd_to_history(t_data *info)
{
	int		i;
	char	*str;

	i = 0;
	if (only_space(info->buf_cmd))
		return ;
	while (info->buf_cmd[i] && info->buf_cmd[i] != '\n')
		i++;
	str = ft_strsub(info->buf_cmd, 0, i);
	ft_push_back(&info->history_list, str);
}

static void	show_history(t_data *info, int max_history_list)
{
	char	*str;

	info->buf_i = ft_strlen(info->buf_cmd);
	str = ft_get_elem(info->history_list, max_history_list - info->num_history);
	del_line(info);
	ft_bzero(info->buf_cmd, info->size_max);
	ft_strlcpy(info->buf_cmd, str, info->size_max);
	write_buf(info);
	info->buf_i = ft_strlen(info->buf_cmd);
}

static void	show_current(t_data *info)
{
	info->buf_i = ft_strlen(info->buf_cmd);
	del_line(info);
	ft_bzero(info->buf_cmd, info->size_max);
	ft_strlcpy(info->buf_cmd, info->tmp_buf, info->size_max);
	write_buf(info);
	info->buf_i = ft_strlen(info->buf_cmd);
	ft_bzero(info->tmp_buf, info->size_max);
}

int			get_history(t_data *info, char *key)
{
	int		max_history_list;

	if (!info->tmp_buf)
		info->tmp_buf = ft_strnew(info->size_max);
	max_history_list = ft_list_size(info->history_list) - 1;
	if (info->num_history == -1)
		ft_strlcpy(info->tmp_buf, info->buf_cmd, info->size_max);
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

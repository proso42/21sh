/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:58:13 by proso             #+#    #+#             */
/*   Updated: 2017/06/18 15:58:14 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void		add_cmd_to_history(t_data *info)
{
	char	*str;

	str = ft_strdup(info->buf_cmd);
	if (info->buf_cmd[0])
		ft_push_back(&info->history_list, str);
}

static void	show_history(t_data *info, int max_history_list)
{
	char	*str;

	str = ft_get_elem(info->history_list, max_history_list - info->num_history);
	del_line(info);
	ft_bzero(info->buf_cmd, 1024);
	ft_strcpy(info->buf_cmd, str);
	write_buf(info);
	info->buf_i = ft_strlen(info->buf_cmd);
}

static void	show_current(t_data *info)
{
	del_line(info);
	ft_bzero(info->buf_cmd, 1024);
	ft_strcpy(info->buf_cmd, info->tmp_buf);
	write_buf(info);
	info->buf_i = ft_strlen(info->buf_cmd);
	ft_bzero(info->tmp_buf, 1024);
}

int			get_history(t_data *info, char *key)
{
	int		max_history_list;

	max_history_list = ft_list_size(info->history_list) - 1;
	if (info->num_history == -1)
		ft_strcpy(info->tmp_buf, info->buf_cmd);
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
	return (2);
}

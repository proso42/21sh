/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 22:40:17 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 00:24:59 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static t_data	*get_info(t_data *info)
{
	static t_data	*p = NULL;

	if (!p)
		p = info;
	return (p);
}

static void		resize_win(int sig)
{
	t_data	*info;

	(void)sig;
	info = get_info(NULL);
	ioctl(0, TIOCGWINSZ, &info->sz);
	clear_sc(info);
	home(info, 0);
	go_good_place(info);
}

static void		kill_process(int sig)
{
	t_data *info;

	(void)sig;
	info = get_info(NULL);
	if (info->quote)
	{
		ioctl(0, TIOCSTI, "");
		info->size_max = 1024;
		ft_strdel(&info->buf_cmd);
		info->buf_cmd = ft_strnew(info->size_max);
		ft_del_tab(info->av);
		info->av = ft_new_array(info->size_max);
		info->buf_i = 0;
		info->curs_x = 0;
		info->curs_y = 0;
		info->pid = -4;
		info->quote = 0;
		term_action(info, "do");
		print_prompt(info);
	}
	else
		exit(-1);
}

void			init_signal(t_data *info)
{
	get_info(info);
	signal(SIGWINCH, resize_win);
	signal(SIGINT, kill_process);
}

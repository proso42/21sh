/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 22:40:17 by proso             #+#    #+#             */
/*   Updated: 2017/10/17 22:59:13 by proso            ###   ########.fr       */
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
	clear_sc(info);
	home(info, 0);
	go_good_place(info);
}

void			init_signal(t_data *info)
{
	get_info(info);
	signal(SIGWINCH, resize_win);
}

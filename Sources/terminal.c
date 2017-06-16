/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 13:05:03 by proso             #+#    #+#             */
/*   Updated: 2017/06/16 13:05:04 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int		default_terminal(t_data *info, int mode)
{
	if ((tcsetattr(0, TCSADRAIN, &info->df_term)) == -1)
		return (error(2));
	if (mode < 0)
		exit (-1);
	return (1);
}

int		init_terminal(t_data *info)
{
	if ((tcgetattr(0, &info->sh_term)) == -1)
		return (error(1));
	if ((tcgetattr(0, &info->df_term)) == -1)
		return (error(1));
	info->sh_term.c_lflag &= ~(ICANON);
	info->sh_term.c_lflag &= ~(ECHO);
	info->sh_term.c_cc[VMIN] = 1;
	info->sh_term.c_cc[VTIME] = 0;
	info->buf_i = 0;
	ioctl(0, TIOCGWINSZ, &info->sz);
	ft_bzero(info->buf_cmd, 1024);
	if ((tcsetattr(0, TCSADRAIN, &info->sh_term)) == -1)
		return (error(2));
	return (1);
}

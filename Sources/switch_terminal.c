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

int			default_terminal(t_data *info, int mode)
{
	if ((tcsetattr(0, TCSADRAIN, &info->df_term)) == -1)
		return (print_error(2));
	if (mode < 0)
		exit(-1);
	return (1);
}

static void	set_var(t_data *info)
{
	info->sh_term.c_lflag &= ~(ICANON);
	info->sh_term.c_lflag &= ~(ECHO);
	info->sh_term.c_cc[VMIN] = 1;
	info->sh_term.c_cc[VTIME] = 0;
	ft_init(0, 4, &info->buf_i, &info->curs_x, &info->curs_y, &info->quote);
	info->env_list = NULL;
	info->root = NULL;
	info->history_list = NULL;
	info->cpy = NULL;
	info->num_history = -1;
	info->pid = -2;
	ioctl(0, TIOCGWINSZ, &info->sz);
	ft_bzero(info->buf_cmd, 1024);
	ft_bzero(info->tmp_buf, 1024);
	ft_bzero(info->av, 10000);
}

int			init_line_edition(t_data *info)
{
	if (!(tgetent(NULL, "xterm-256color")))
		return (print_error(3));
	if ((tcgetattr(0, &info->sh_term)) == -1)
		return (print_error(1));
	if ((tcgetattr(0, &info->df_term)) == -1)
		return (print_error(1));
	info->sh_term.c_lflag &= ~(ICANON);
	info->sh_term.c_lflag &= ~(ECHO);
	info->sh_term.c_cc[VMIN] = 1;
	info->sh_term.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSADRAIN, &info->sh_term)) == -1)
		return (print_error(2));
	return (0);
}

int			init_terminal(t_data *info)
{
	if (!(tgetent(NULL, "xterm-256color")))
		return (print_error(3));
	if ((tcgetattr(0, &info->sh_term)) == -1)
		return (print_error(1));
	if ((tcgetattr(0, &info->df_term)) == -1)
		return (print_error(1));
	set_var(info);
	if ((tcsetattr(0, TCSADRAIN, &info->sh_term)) == -1)
		return (print_error(2));

	return (1);
}

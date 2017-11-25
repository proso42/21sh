/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 13:05:03 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 00:23:20 by proso            ###   ########.fr       */
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
	info->root = NULL;
	info->env_list = NULL;
	info->history_list = NULL;
	info->lexem_list = NULL;
	info->cpy = NULL;
	info->num_history = -1;
	info->pid = -2;
	info->searching = 0;
	ioctl(0, TIOCGWINSZ, &info->sz);
	info->size_max = 1024;
	info->buf_cmd = ft_strnew(info->size_max);
	info->tmp_buf = NULL;
	info->av = ft_new_array(info->size_max);
	if (!(info->hist = (t_hist*)malloc(sizeof(t_hist))))
		print_error(ERR_MALLOC);
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

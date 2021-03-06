/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:56:00 by proso             #+#    #+#             */
/*   Updated: 2017/11/29 01:05:03 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void		print_prompt(t_data *info)
{
	char	*str;

	str = ft_strnew(info->size_max);
	if (!info->quote)
	{
		getcwd(str, info->size_max);
		if (!str[0])
			ft_strcpy(str, "21sh");
		ft_strlcat(str, " $> ", info->size_max);
		ft_printf("{blue}{bold}%s{res}", str);
	}
	if (info->quote == 1)
		ft_strlcpy(str, "quote> ", info->size_max);
	else if (info->quote == 2)
		ft_strlcpy(str, "dquote> ", info->size_max);
	if (info->quote)
		ft_putstr(str);
	info->prompt_size = ft_strlen(str);
	if (info->prompt_size >= info->sz.ws_col)
		info->curs_x = (info->prompt_size - info->sz.ws_col);
	else
		info->curs_x = info->prompt_size;
	info->curs_y = info->prompt_size / info->sz.ws_col;
	ft_strdel(&str);
}

static void	print_entry(t_data *info)
{
	ft_putstr_color("+-----------------------+\n", C_GREEN);
	ft_putstr_color("|                       |\n", C_GREEN);
	ft_putstr_color("|    Welcome connard    |\n", C_GREEN);
	ft_putstr_color("|       the 21sh        |\n", C_GREEN);
	ft_putstr_color("|                       |\n", C_GREEN);
	ft_putstr_color("+-----------------------+\n", C_GREEN);
	print_prompt(info);
}

static void	init(t_data *info)
{
	init_terminal(info);
	info->env_list = init_env_list();
	create_min_env_var(info);
	init_signal(info);
	print_entry(info);
}

static void	new_prompt(t_data *info, int ret)
{
	print_prompt(info);
	ft_strdel(&info->buf_cmd);
	info->size_max = 1024;
	info->buf_cmd = ft_strnew(info->size_max);
	info->buf_i = 0;
	btree_remove_all(&info->root, del);
	ft_remove_list(&info->lexem_list);
	if (ret != 2 && ret != 54)
	{
		info->num_history = -1;
		info->pid = -2;
	}
}

int			main(void)
{
	t_data	info;
	int		ret;

	init(&info);
	while (1)
	{
		if (!(ret = get_stdin(&info)))
		{
			end(&info);
			term_action(&info, "do");
			if (!info.quote)
			{
				if (!(start_with_operand(info.buf_cmd)) &&
								info.buf_cmd[0] && !only_space(info.buf_cmd))
					lexer(&info);
			}
			new_prompt(&info, ret);
		}
	}
	return (0);
}

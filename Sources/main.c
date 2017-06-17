/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:56:00 by proso             #+#    #+#             */
/*   Updated: 2017/06/16 12:56:02 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void		print_prompt(t_data *info)
{
	char	str[1024];

	ft_bzero(str, 1024);
	getcwd(str, 1024);
	ft_printf("{blue}{bold}%s $> {res}", str);
	info->prompt_size = ft_strlen(str) + 4;
	if (info->prompt_size >= info->sz.ws_col)
		info->curs_x = (info->prompt_size - info->sz.ws_col);
	else
		info->curs_x = info->prompt_size;
	info->curs_y = info->prompt_size / info->sz.ws_col;
}

static void	print_entry(t_data *info)
{
	ft_putstr_color("+-----------------------+\n", C_GREEN);
	ft_putstr_color("|                       |\n", C_GREEN);
	ft_putstr_color("|    Bienvenue dans     |\n", C_GREEN);
	ft_putstr_color("|       le 21sh         |\n", C_GREEN);
	ft_putstr_color("|                       |\n", C_GREEN);
	ft_putstr_color("+-----------------------+\n", C_GREEN);
	print_prompt(info);
}

int			main(void)
{
	t_data	info;

	init_terminal(&info);
	print_entry(&info);
	while (1)
	{
		get_stdin(&info);
	}
	return (0);
}

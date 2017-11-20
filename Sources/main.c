/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:56:00 by proso             #+#    #+#             */
/*   Updated: 2017/11/21 00:40:57 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void		print_prompt(t_data *info)
{
	char	str[1024];

	ft_bzero(str, 1024);
	if (!info->quote)
	{
		getcwd(str, 1024);
		if (!str[0])
			ft_strlcpy(str, "21sh", 1024);
		ft_printf("{blue}{bold}%s{res}", ft_strcat(str, " $> "));
	}
	else if (info->quote == 1)
		ft_printf("%s", ft_strlcpy(str, "quote> ", 1024));
	else if (info->quote == 2)
		ft_printf("%s", ft_strlcpy(str, "dquote> ", 1024));
	info->prompt_size = ft_strlen(str);
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
	ft_putstr_color("|    Welcome connard    |\n", C_GREEN);
	ft_putstr_color("|       the 21sh        |\n", C_GREEN);
	ft_putstr_color("|                       |\n", C_GREEN);
	ft_putstr_color("+-----------------------+\n", C_GREEN);
	print_prompt(info);
}

/*static void	print_av(t_data *info)
{
	int		i = 0;

	while (info->av[i][0])
	{
		ft_printf("\n{bold}{cyan}%s{res}", info->av[i]);
		i++;
	}
}*/

static void	init(t_data *info)
{
	init_terminal(info);
	info->env_list = init_env_list();
	create_min_env_var(info);
	init_signal(info);
	print_entry(info);
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
			lexer(&info);
	//		print_av(&info);		// À RETIRER
			print_prompt(&info);
			ft_bzero(info.buf_cmd, 1024);
			ft_bzero(info.av, 10000);
			info.buf_i = 0;
			btree_remove_all(&info.root, del);
			ft_remove_list(&info.lexem_list);
		}
		if (ret != 2 && ret != 54)
		{
			info.num_history = -1;
			info.pid = -2;
		}
	}
	return (0);
}

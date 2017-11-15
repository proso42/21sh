/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 15:27:24 by proso             #+#    #+#             */
/*   Updated: 2017/11/16 00:40:46 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int		term_error(int err)
{
	if (err == 1)
		ft_putstr_color("21sh: Fatal error with tcgetattr function...\n"
																	, C_RED);
	else if (err == 2)
		ft_putstr_color("21sh: Fatal error with tcsetattr function...\n"
																	, C_RED);
	else if (err == 3)
		ft_putstr_color("21sh: Fatal error with tgetent function...\n", C_RED);
	exit(-1);
	return (-1);
}

static int		env_error(int err)
{
	if (err == 5)
		ft_putstr_color("21sh: Unknow env variable...\n", C_RED);
	else if (err == 6)
		ft_putstr_color("21sh: Missing HOME env variable...\n", C_RED);
	else if (err == 7)
		ft_putstr_color("21sh: Missing OLDPWD env variable...\n", C_RED);
	else if (err == 12)
		ft_putstr_color("21sh: Missing PATH env variable...\n", C_RED);
	return (-1);
}

static int		args_error(int err)
{
	if (err == 8)
		ft_putstr_color("21sh: Too few arguments !\n", C_RED);
	else if (err == 9)
		ft_putstr_color("21sh: Too many arguments !\n", C_RED);
	else if (err == EMPTY_HIST)
	{
		ft_printf("\n{red}{bold}21sh: Empty hitoric{res}");
		return (0);
	}
	return (-1);
}

int				print_error(int err)
{
	if (err == 1 || err == 2 || err == 3)
		return (term_error(err));
	else if (err == 5 || err == 6 || err == 7)
		return (env_error(err));
	else if (err == 8 || err == 9 || err == EMPTY_HIST)
		return (args_error(err));
	else if (err == ERR_MALLOC)
	{
		ft_putstr_color("21sh: Fail to allocate memory with malloc function\n"
																	, C_RED);
		exit(-1);
	}
	else if (err == ERR_TERM)
		ft_putstr_color("21sh: Fatal error with tgetstr/tputs function...\n"
																	, C_RED);
	else if (err == ERR_INEXISTANT)
		ft_putstr_color("21sh: No such file or directory\n", C_RED);
	else if (err == PERMISSION)
		ft_putstr_color("21sh: Permission denied\n", C_RED);
	else if (err == ERR_DIRECTORY)
		ft_putstr_color("21sh: Not a directory\n", C_RED);
	else if (err == 10)
		ft_putstr_color("21sh: Numeric argument required\n", C_RED);
	else if (err == 11)
		ft_putstr_color("21sh: Command line cannot start with an operand\n"
																	, C_RED);
	return (-1);
}

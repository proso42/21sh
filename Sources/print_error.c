/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 15:27:24 by proso             #+#    #+#             */
/*   Updated: 2017/06/17 15:27:26 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int		term_error(int err)
{
	if (err == 1)
		ft_putstr_color("Fatal error with tcgetattr function...\n", C_RED);
	else if (err == 2)
		ft_putstr_color("Fatal error with tcsetattr function...\n", C_RED);
	else if (err == 3)
		ft_putstr_color("Fatal error with tgetent function...\n", C_RED);
	return (-1);
}

static int		env_error(int err)
{
	if (err == 5)
		ft_putstr_color("\nUnknow env variable...", C_RED);
	return (-1);
}

int				print_error(int err)
{
	if (err == 1 || err == 2 || err == 3)
		return (term_error(err));
	else if (err == 5)
		return (env_error(err));
	else if (err == ERR_MALLOC)
	{
		ft_putstr_color("Fail to allocate memory with malloc function\n"
																	, C_RED);
		exit(-1);
	}
	else if (err == ERR_TERM)
		ft_putstr_color("Fatal error with tgetstr/tputs function...\n", C_RED);
	else if (err == INEXISTANT)
		ft_putstr_color("No such file or directory\n", C_RED);
	else if (err == PERMISSION)
		ft_putstr_color("Permission denied\n", C_RED);
	return (-1);
}

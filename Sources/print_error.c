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

int		term_error(int err)
{
	if (err == 1)
		ft_putstr_color("Fatal error with tcgetattr function...\n", C_RED);
	else if (err == 2)
		ft_putstr_color("Fatal error with tcsetattr function...\n", C_RED);
	else if (err == 3)
		ft_putstr_color("Fatal error with tgetent function...\n", C_RED);
	return (-1);
}

int		print_error(int err)
{
	if (err == 1 || err == 2 || err == 3)
		return (term_error(err));
	else if (err == ERR_MALLOC)
		ft_putstr_color("Fail to allocate memory with malloc function\n"
																	, C_RED);
	else if (err == ERR_TERM)
		ft_putstr_color("Fatal error with tgetstr/tputs function...\n", C_RED);
	return (-1);
}

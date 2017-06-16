/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 13:11:52 by proso             #+#    #+#             */
/*   Updated: 2017/06/16 13:11:53 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int		term_error(int err)
{
	if (err == 1)
		ft_putstr_color("Fatal error with tcgetattr function...\n", C_RED);
	else if (err == 2)
		ft_putstr_color("Fatal error with tcsetattr function...\n", C_RED);
	return (-1);
}

int		error(int err)
{
	if (err == 1 || err == 2)
		return (term_error(err));
	else if (err == ERR_MALLOC)
		ft_putstr_color("Fail to allocate memory with malloc function\n"
																	, C_RED);
	else if (err == ERR_TERM)
		ft_putstr_color("Fatal error with tgetstr/tputs function...\n", C_RED);
	return (-1);
}

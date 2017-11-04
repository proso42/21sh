/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 13:17:32 by proso             #+#    #+#             */
/*   Updated: 2017/11/04 02:10:22 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	term_action(t_data *info, char *action)
{
	if ((tputs(tgetstr(action, NULL), 0, ft_out)) < 0)
	{
		print_error(ERR_TERM);
		default_terminal(info, -1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 13:17:32 by proso             #+#    #+#             */
/*   Updated: 2017/06/16 13:17:33 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	term_action(char *action)
{
	if (tputs(tgetstr(action, NULL), 0, ft_out) <= 0)
	{
		error(ERR_TERM);
		exit(-1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_on_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 01:40:23 by proso             #+#    #+#             */
/*   Updated: 2017/11/13 00:34:04 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int		exectute(t_data *info, t_lexem *lex)
{
	if (start_with_operand(info->av[0]))
		return (print_error(11));
	if (is_builtin(lex))
		return (exec_builtin(info, lex));
	else
		return (exec_single(info, lex));
}

void	del(void *lex)
{
	ft_del_tab(((t_lexem*)lex)->cmd);
}

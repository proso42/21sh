/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_on_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 01:40:23 by proso             #+#    #+#             */
/*   Updated: 2017/12/01 02:10:27 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int		exectute(t_data *info, t_lexem *lex)
{
	if (is_builtin(lex))
		return (exec_builtin(info, lex));
	else
		return (exec_single(info, lex));
}

void	del(void *lex)
{
	ft_del_tab(((t_lexem*)lex)->cmd);
}

int		is_builtin(t_lexem *lex)
{
	if (!lex->cmd || !lex->cmd[0])
		return (0);
	else if (!ft_strcmp(lex->cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(lex->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(lex->cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(lex->cmd[0], "setenv"))
		return (1);
	else if (!ft_strcmp(lex->cmd[0], "unsetenv"))
		return (1);
	else if (!ft_strcmp(lex->cmd[0], "echo"))
		return (1);
	return (0);
}

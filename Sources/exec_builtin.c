/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:12:25 by proso             #+#    #+#             */
/*   Updated: 2017/11/13 00:34:49 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int	exec_builtin(t_data *info, t_lexem *lex)
{
	if (!(ft_strcmp(lex->cmd[0], "env")))
		return (builtin_env(info, lex->cmd));
	else if (!(ft_strcmp(lex->cmd[0], "setenv")))
		return (builtin_setenv(info, lex->cmd));
	else if (!(ft_strcmp(lex->cmd[0], "unsetenv")))
		return (builtin_unsetenv(info, lex->cmd));
	else if (!(ft_strcmp(lex->cmd[0], "cd")))
		return (builtin_cd(info, lex->cmd[1]));
	else if (!(ft_strcmp(lex->cmd[0], "echo")))
		return (builtin_echo(lex->cmd));
	else if (!(ft_strcmp(lex->cmd[0], "exit")))
		return (builtin_exit(lex->cmd));
	return (1);
}

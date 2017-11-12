/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:12:25 by proso             #+#    #+#             */
/*   Updated: 2017/11/10 02:59:09 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	exec_builtin(t_data *info, t_lexem *lex)
{
	if (!(ft_strcmp(lex->cmd[0], "env")))
		builtin_env(info, lex->cmd);
	else if (!(ft_strcmp(lex->cmd[0], "setenv")))
		builtin_setenv(info, lex->cmd);
	else if (!(ft_strcmp(lex->cmd[0], "unsetenv")))
		builtin_unsetenv(info, lex->cmd);
	else if (!(ft_strcmp(lex->cmd[0], "cd")))
		builtin_cd(info, lex->cmd[1]);
	else if (!(ft_strcmp(lex->cmd[0], "echo")))
		builtin_echo(lex->cmd);
	else if (!(ft_strcmp(lex->cmd[0], "exit")))
		builtin_exit(lex->cmd);
}

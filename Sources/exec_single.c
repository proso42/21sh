/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 16:19:42 by proso             #+#    #+#             */
/*   Updated: 2017/11/12 01:31:22 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int		exec_single(t_data *info, t_lexem *lex)
{
	char	**envp;
	char	*path;
	pid_t	child;

	envp = ft_list_to_tab(info->env_list);
	if (!(path = find_cmd(info, lex->cmd[0])))
		return (0);
	child = fork();
	info->pid = child;
	if (!child && lex->cmd[0])
	{
		execve(path, lex->cmd, envp);
		ft_del_tab(envp);
		ft_strdel(&path);
		exit(0);
	}
	if (lex->cmd[0] && lex->cmd[0][0])
		wait(&child);
	return (1);
}

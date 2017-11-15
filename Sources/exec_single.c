/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 16:19:42 by proso             #+#    #+#             */
/*   Updated: 2017/11/14 00:07:39 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static char	**get_env_tab(t_list *env_list)
{
	t_list	*current;
	char	**env_tab;
	int		i;

	if (!env_list)
		return (NULL);
	if (!(env_tab = (char**)malloc(sizeof(char*) * ft_list_size(env_list) + 1)))
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		env_tab[i] = ft_strdup(((t_env*)current->data)->env_complete);
		i++;
		current = current->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

int			exec_single(t_data *info, t_lexem *lex)
{
	char	**envp;
	char	*path;
	pid_t	child;

	envp = get_env_tab(info->env_list);
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
	if (WEXITSTATUS(child))
		return (0);
	return (1);
}

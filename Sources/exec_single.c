/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 16:19:42 by proso             #+#    #+#             */
/*   Updated: 2017/10/18 00:00:38 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static char	**get_args(t_data *info)
{
	int		i;
	char	**args;

	i = 0;
	while (info->av[i][0])
		i++;
	if (!(args = (char**)malloc(sizeof(char*) * i)))
	{
		ft_putstr_color("Fail to allocate memory with malloc function\n"
																	, C_RED);
		exit(-1);
	}
	i = 0;
	while (info->av[i][0])
	{
		args[i] = info->av[i];
		i++;
	}
	args[i] = NULL;
	return (args);
}

void		exec_single(t_data *info)
{
	char	**envp;
	char	**args;
	pid_t	child;

	envp = ft_list_to_tab(info->env_list);
	args = get_args(info);
	child = fork();
	if (!child && info->av[0])
	{
		execve(info->av[0], args, envp);
		free(envp);
		exit(0);
	}
	if (info->av[0][0])
		wait(&child);
}

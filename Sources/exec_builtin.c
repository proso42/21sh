/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:12:25 by proso             #+#    #+#             */
/*   Updated: 2017/11/05 01:37:11 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	exec_builtin(t_data *info, int i)
{
	if (!(ft_strcmp(info->av[i], "env")))
		builtin_env(info);
	else if (!(ft_strcmp(info->av[i], "setenv")))
		builtin_setenv(info, info->av[i + 1], info->av[i + 2]);
	else if (!(ft_strcmp(info->av[i], "unsetenv")))
		builtin_unsetenv(info);
	else if (!(ft_strcmp(info->av[i], "cd")))
		builtin_cd(info);
	else if (!(ft_strcmp(info->av[i], "echo")))
		builtin_echo(info);
	else if (!(ft_strcmp(info->av[i], "exit")))
		builtin_exit(info);
}

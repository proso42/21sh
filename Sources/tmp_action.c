/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:12:25 by proso             #+#    #+#             */
/*   Updated: 2017/10/16 00:12:29 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	tmp_action(t_data *info)
{
	if (!(ft_strcmp(info->av[0], "env")))
		builtin_env(info);
	else if (!(ft_strcmp(info->av[0], "setenv")))
		builtin_setenv(info, info->av[1], info->av[2]);
	else if (!(ft_strcmp(info->av[0], "unsetenv")))
		builtin_unsetenv(info);
	else if (!(ft_strcmp(info->av[0], "cd")))
		builtin_cd(info);
}

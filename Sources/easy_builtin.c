/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:04:11 by proso             #+#    #+#             */
/*   Updated: 2017/10/16 03:49:10 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	builtin_echo(t_data *info)
{
	int		i = 1;

	if (info->av[i][0])
		write(0, "\n", 1);
	while (info->av[i][0])
	{
		ft_printf("%s", info->av[i]);
		i++;
		if (info->av[i][0])
			write(0, " ", 1);
	}
}

void	builtin_exit(int ret)
{
	exit(ret);
}

void	builtin_env(t_data *info)
{
	t_list	*current;

	current = info->env_list;
	while (current)
	{
		write(0, "\n", 1);
		ft_putstr(((t_env*)(current->data))->env_complete);
		current = current->next;
	}
}

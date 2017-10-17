/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:04:11 by proso             #+#    #+#             */
/*   Updated: 2017/10/17 23:59:27 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	builtin_echo(t_data *info)
{
	int		i;

	i = 1;
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

void	builtin_exit(t_data *info)
{
	int		ret;

	if (info->av[2][0])
	{
		print_error(9);
		return ;
	}
	else if (!(info->av[1][0]))
		ret = 0;
	else
		ret = ft_atoi(info->av[1]);
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

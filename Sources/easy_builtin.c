/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:04:11 by proso             #+#    #+#             */
/*   Updated: 2017/11/12 01:36:20 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void	builtin_echo(char **arg)
{
	int		i;

	i = 1;
	while (arg[i] && arg[i][0])
	{
		ft_printf("%s\n", arg[i]);
		i++;
		if (arg[i] && arg[i][0])
			write(0, " ", 1);
	}
}

void	builtin_exit(char **arg)
{
	int		ret;
	int		i;

	i = 0;
	if (arg[0] && arg[1] && arg[2] && arg[2][0])
	{
		print_error(9);
		return ;
	}
	else if (!(arg[1]))
		exit(0);
	else
		ret = ft_atoi(arg[1]);
	while (arg[1][i])
	{
		if (!ft_isdigit(arg[1][i]))
		{
			print_error(10);
			exit(255);
		}
		i++;
	}
	exit(ret);
}

void	builtin_env(t_data *info, char **arg)
{
	t_list	*current;

	if (arg[1])
	{
		print_error(9);
		return ;
	}
	current = info->env_list;
	while (current)
	{
		ft_putendl(((t_env*)(current->data))->env_complete);
		current = current->next;
	}
}

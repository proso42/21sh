/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:04:11 by proso             #+#    #+#             */
/*   Updated: 2017/11/30 01:23:23 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int	builtin_echo(char **arg)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if (i > 1 && arg[i - 1][0])
			write(0, " ", 1);
		ft_printf("%s", arg[i]);
		i++;
	}
	write(0, "\n", 1);
	return (1);
}

int	builtin_exit(t_data *info, char **arg)
{
	int		ret;
	int		i;

	i = 0;
	if (arg[0] && arg[1] && arg[2] && arg[2][0])
	{
		print_error(9);
		return (0);
	}
	else if (!(arg[1]))
		default_terminal(info, 0);
	else
		ret = ft_atoi(arg[1]);
	while (arg[1][i])
	{
		if (!ft_isdigit(arg[1][i]))
		{
			print_error(10);
			default_terminal(info, 255);
		}
		i++;
	}
	default_terminal(info, ret);
	return (1);
}

int	builtin_env(t_data *info, char **arg)
{
	t_list	*current;

	if (arg[1])
	{
		print_error(9);
		return (0);
	}
	current = info->env_list;
	while (current)
	{
		ft_putendl(((t_env*)(current->data))->env_complete);
		current = current->next;
	}
	return (1);
}

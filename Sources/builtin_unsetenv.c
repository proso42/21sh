/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:07:56 by proso             #+#    #+#             */
/*   Updated: 2017/11/14 00:06:40 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int			check_var(t_list *env_list, char *env)
{
	t_list	*current;
	int		i;

	i = 0;
	if (!(current = env_list))
		return (-1);
	while (current)
	{
		if (!(ft_strcmp(env, ((t_env*)(current->data))->env_name)))
			return (i);
		current = current->next;
		i++;
	}
	return (-1);
}

static void	del_env_var(t_data *info, char *env)
{
	int		index;

	if ((index = check_var(info->env_list, env)) < 0)
		print_error(5);
	else
	{
		ft_clear_elem(&info->env_list, ft_get_p_elem(info->env_list, index));
		ft_putstr_color("Env varaible successfully deleted !\n", C_GREEN);
	}
}

int			builtin_unsetenv(t_data *info, char **arg)
{
	int		i;

	i = 1;
	if (!arg[1] || !arg[1][0])
	{
		print_error(8);
		return (0);
	}
	while (arg[i] && arg[i][0])
	{
		del_env_var(info, arg[i]);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:07:56 by proso             #+#    #+#             */
/*   Updated: 2017/10/16 00:07:58 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int	check_var(t_list *env_list, char *env)
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
		ft_putstr_color("\nEnv varaible successfully deleted !", C_GREEN);
	}
}

void		builtin_unsetenv(t_data *info)
{
	int		i;

	i = 1;
	if (!info->av[1] || !info->av[1][0])
		print_error(8);
	while (info->av[i][0])
	{
		del_env_var(info, info->av[i]);
		i++;
	}
}

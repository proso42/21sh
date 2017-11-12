/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 14:55:14 by proso             #+#    #+#             */
/*   Updated: 2017/11/11 01:39:41 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int	check_nb_arg(char **arg)
{
	if (!arg[1] || !arg[2])
	{
		print_error(8);
		return (0);
	}
	else if (arg[1] && arg[2] && arg[3])
	{
		print_error(9);
		return (0);
	}
	return (1);
}

void		builtin_setenv(t_data *info, char **arg)
{
	t_list	*env_list;
	t_env	*var;

	if (!check_nb_arg(arg))
		return ;
	env_list = ft_get_p_elem(info->env_list, check_var(info->env_list, arg[1]));
	if (!env_list)
	{
		if (!(var = (t_env*)malloc(sizeof(t_env))))
			print_error(ERR_MALLOC);
		var->env_name = ft_strdup(arg[1]);
		var->env_value = ft_strdup(arg[2]);
		var->env_complete = ft_strjoin(arg[1], "=");
		var->env_complete = ft_strjoinfree(var->env_complete, arg[2], 1);
		ft_push_back(&info->env_list, var);
	}
	else
	{
		ft_strdel(&((t_env*)(env_list->data))->env_value);
		ft_strdel(&((t_env*)(env_list->data))->env_complete);
		((t_env*)(env_list->data))->env_value = ft_strdup(arg[2]);
		((t_env*)(env_list->data))->env_complete = ft_strjoin(arg[1], "=");
		((t_env*)(env_list->data))->env_complete = ft_strjoinfree(
						((t_env*)(env_list->data))->env_complete, arg[2], 1);
	}
}

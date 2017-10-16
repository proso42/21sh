/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 14:55:14 by proso             #+#    #+#             */
/*   Updated: 2017/09/13 14:55:16 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int	check_nb_arg(t_data *info, char *env, char *value)
{
	if (!env[0] || !value[0])
	{
		print_error(8);
		return (0);
	}
	else if (info->av[1][0] && info->av[2][0] && info->av[3][0])
	{
		print_error(9);
		return (0);
	}
	return (1);
}

void		builtin_setenv(t_data *info, char *env, char *value)
{
	t_list	*env_list;
	t_env	*var;

	if (!check_nb_arg(info, env, value))
		return;
	env_list = ft_get_p_elem(info->env_list, check_var(info->env_list, env));
	if (!env_list)
	{
		if (!(var = (t_env*)malloc(sizeof(t_env))))
			print_error(ERR_MALLOC);
		var->env_name = ft_strdup(env);
		var->env_value = ft_strdup(value);
		var->env_complete = ft_strjoin(env, "=");
		var->env_complete = ft_strjoinfree(var->env_complete, value, 1);
		ft_push_back(&info->env_list, var);
	}
	else
	{
		ft_strdel(&((t_env*)(env_list->data))->env_value);
		ft_strdel(&((t_env*)(env_list->data))->env_complete);
		((t_env*)(env_list->data))->env_value = ft_strdup(value);
		((t_env*)(env_list->data))->env_complete = ft_strjoin(env, "=");
		((t_env*)(env_list->data))->env_complete = ft_strjoinfree(
							((t_env*)(env_list->data))->env_complete, value, 1);
	}
}

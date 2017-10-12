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

void		builtin_setenv(t_data *info, char *env, char *value)
{
	t_list	*var;
	t_env	*new_env_var;

	new_env_var = NULL;
	var = ft_get_p_elem(info->env_list, check_var(info->env_list, env));
	if (!var)
	{
		if (!(new_env_var = (t_env*)malloc(sizeof(t_env))))
			print_error(ERR_MALLOC);
		new_env_var->env_name = ft_strdup(env);
		new_env_var->env_value = ft_strdup(value);
		new_env_var->env_complete = ft_strjoin(env, "=");
		new_env_var->env_complete = ft_strjoinfree(new_env_var->env_complete,
																	value, 1);
		ft_push_back(&info->env_list, new_env_var);
	}
	else
	{
		ft_strdel(&((t_env*)(var->data))->env_value);
		ft_strdel(&((t_env*)(var->data))->env_complete);
		((t_env*)(var->data))->env_value = ft_strdup(value);
		((t_env*)(var->data))->env_complete = ft_strjoin(env, "=");
		((t_env*)(var->data))->env_complete = ft_strjoinfree(
								((t_env*)(var->data))->env_complete, value, 1);
	}
}

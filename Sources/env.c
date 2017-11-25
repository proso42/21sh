/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 16:14:00 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 00:18:05 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

char		*get_env_var(t_data *info, char *str)
{
	t_list	*current;

	current = info->env_list;
	while (current)
	{
		if (!(ft_strcmp((((t_env*)(current->data))->env_name), str)))
			return (((t_env*)(current->data))->env_value);
		current = current->next;
	}
	return (NULL);
}

static void	update_pwd(t_data *info)
{
	int		i;
	char	str[info->size_max];
	char	**arg;

	if ((i = check_var(info->env_list, "PWD")) < 0)
	{
		arg = ft_set_array(3, "setenv", "PWD", getcwd(str, info->size_max));
		builtin_setenv(info, arg);
		ft_del_tab(arg);
	}
}

void		create_min_env_var(t_data *info)
{
	int		i;
	int		shlvl;
	char	*new_shlvl;
	char	**arg;

	arg = NULL;
	if ((i = check_var(info->env_list, "SHLVL")) < 0)
	{
		arg = ft_set_array(3, "setenv", "SHLVL", "1");
		builtin_setenv(info, arg);
	}
	else
	{
		shlvl = ft_atoi(((t_env*)
						(ft_get_p_elem(info->env_list, i))->data)->env_value);
		new_shlvl = (shlvl < -1 || shlvl == 2147483647) ?
											ft_strdup("0") : ft_itoa(shlvl + 1);
		arg = ft_set_array(3, "setenv", "SHLVL", new_shlvl);
		builtin_setenv(info, arg);
		ft_strdel(&new_shlvl);
	}
	update_pwd(info);
	ft_del_tab(arg);
}

t_list		*init_env_list(void)
{
	extern char	**environ;
	t_list		*list;
	t_env		*var;
	int			i;

	i = 0;
	list = NULL;
	while (environ[i])
	{
		if (!(var = (t_env*)malloc(sizeof(t_env))))
			exit(print_error(ERR_MALLOC));
		var->env_complete = ft_strdup(environ[i]);
		var->env_name = ft_strcdup(environ[i], '=');
		var->env_value = ft_strcsub(environ[i], '=');
		ft_push_back(&list, var);
		i++;
	}
	return (list);
}

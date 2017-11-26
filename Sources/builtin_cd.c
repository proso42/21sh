/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:07:42 by proso             #+#    #+#             */
/*   Updated: 2017/11/26 00:57:29 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int	replace_minus(t_data *info, char *path)
{
	t_list	*o_pwd;
	char	*minus;

	o_pwd = ft_get_p_elem(info->env_list, check_var(info->env_list, "OLDPWD"));
	if (!o_pwd)
		return (0);
	minus = ((t_env*)(o_pwd->data))->env_value;
	ft_bzero(path, info->size_max);
	ft_strlcpy(path, minus, info->size_max);
	return (1);
}

static int	change_current_dir(t_data *info, char *new_pwd)
{
	char	old_pwd[info->size_max];
	char	pwd[info->size_max];
	char	**arg;

	getcwd(old_pwd, info->size_max);
	arg = ft_set_array(3, "setenv", "OLDPWD", old_pwd);
	builtin_setenv(info, arg);
	chdir(new_pwd);
	getcwd(pwd, info->size_max);
	ft_del_tab(arg);
	arg = ft_set_array(3, "setenv", "PWD", pwd);
	builtin_setenv(info, arg);
	ft_del_tab(arg);
	return (1);
}

static int	change_to_home(t_data *info)
{
	char	old_pwd[info->size_max];
	t_list	*pwd;
	char	*home;
	char	**arg;

	getcwd(old_pwd, info->size_max);
	arg = ft_set_array(3, "setenv", "OLDPWD", old_pwd);
	builtin_setenv(info, arg);
	pwd = ft_get_p_elem(info->env_list, check_var(info->env_list, "HOME"));
	if (!pwd)
	{
		ft_del_tab(arg);
		return (print_error(6));
	}
	home = ((t_env*)(pwd->data))->env_value;
	chdir(home);
	ft_del_tab(arg);
	arg = ft_set_array(3, "setenv", "PWD", home);
	builtin_setenv(info, arg);
	ft_del_tab(arg);
	return (1);
}

int			builtin_cd(t_data *info, char *path)
{
	char	tmp[info->size_max];

	ft_bzero(tmp, info->size_max);
	if (!path)
		return (change_to_home(info));

	if (!(ft_strcmp(path, "-")))
	{
		if (!replace_minus(info, tmp))
			return (print_error(7));
	}
	else
		ft_strlcpy(tmp, path, info->size_max);
	if ((check_path_error(tmp, 1, 1)) < 0)
		return (-1);
	change_current_dir(info, tmp);
	return (1);
}

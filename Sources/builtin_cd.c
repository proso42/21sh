/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:07:42 by proso             #+#    #+#             */
/*   Updated: 2017/11/12 00:44:12 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int	replace_tild(t_data *info, char *path)
{
	t_list	*home;
	char	*tild;
	char	tmp[100];

	home = ft_get_p_elem(info->env_list, check_var(info->env_list, "HOME"));
	if (!home)
		return (0);
	tild = ((t_env*)(home->data))->env_value;
	ft_bzero(tmp, 100);
	ft_strcpy(tmp, path + 1);
	ft_bzero(path, 100);
	ft_strcpy(path, tild);
	ft_strcpy(path + ft_strlen(tild), tmp);
	return (1);
}

static int	replace_minus(t_data *info, char *path)
{
	t_list	*o_pwd;
	char	*minus;

	o_pwd = ft_get_p_elem(info->env_list, check_var(info->env_list, "OLDPWD"));
	if (!o_pwd)
		return (0);
	minus = ((t_env*)(o_pwd->data))->env_value;
	ft_bzero(path, 100);
	ft_strcpy(path, minus);
	return (1);
}

static int	change_current_dir(t_data *info, char *new_pwd)
{
	char	old_pwd[126];
	char	pwd[126];
	char	**arg;

	if (!(arg = (char**)malloc(sizeof(char*) * 3)))
		return (print_error(ERR_MALLOC));
	getcwd(old_pwd, 126);
	arg = ft_set_array(3, "setenv", "OLDPWD", old_pwd);
	builtin_setenv(info, arg);
	chdir(new_pwd);
	getcwd(pwd, 126);
	ft_del_tab(arg);
	arg = ft_set_array(3, "setenv", "PWD", pwd);
	builtin_setenv(info, arg);
	ft_del_tab(arg);
	return (1);
}

static int	change_to_home(t_data *info)
{
	char	old_pwd[126];
	t_list	*pwd;
	char	*home;
	char	**arg;

	if (!(arg = (char**)malloc(sizeof(char*) * 3)))
		return (print_error(ERR_MALLOC));
	getcwd(old_pwd, 126);
	arg = ft_set_array(3, "setenv", "OLDPWD", old_pwd);
	builtin_setenv(info, arg);
	pwd = ft_get_p_elem(info->env_list, check_var(info->env_list, "HOME"));
	if (!pwd)
		return (print_error(6));
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
	char	tmp[100];

	ft_bzero(tmp, 100);
	if (!path)
		return (change_to_home(info));
	if (path[0] == '~')
	{
		if (!replace_tild(info, tmp))
			return (print_error(6));
	}
	else if (!(ft_strcmp(path, "-")))
	{
		if (!replace_minus(info, tmp))
			return (print_error(7));
	}
	else
		ft_strcpy(tmp, path);
	if ((check_path_error(tmp, 1, 1)) < 0)
		return (-1);
	change_current_dir(info, tmp);
	return (1);
}

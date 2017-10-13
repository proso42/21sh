#include "../Includes/shell.h"

static int	replace_tild(t_data *info)
{
	t_list	*home;
	char	*tild;
	char	tmp[100];

	home = ft_get_p_elem(info->env_list, check_var(info->env_list, "HOME"));
	if (!home)
		return (0);
	tild = ((t_env*)(home->data))->env_value;
	ft_bzero(tmp, 100);
	ft_strcpy(tmp, info->av[1] + 1);
	ft_bzero(info->av[1], 100);
	ft_strcpy(info->av[1], tild);
	ft_strcpy(info->av[1] + ft_strlen(tild), tmp);
	return (1);
}

static int	replace_minus(t_data *info)
{
	t_list	*o_pwd;
	char	*minus;

	o_pwd = ft_get_p_elem(info->env_list, check_var(info->env_list, "OLDPWD"));
	if (!o_pwd)
		return (0);
	minus = ((t_env*)(o_pwd->data))->env_value;
	ft_bzero(info->av[1], 100);
	ft_strcpy(info->av[1], minus);
	return (1);
}

static void	change_current_dir(t_data *info, char *new_pwd)
{
	char	old_pwd[126];
	char	pwd[126];

	getcwd(old_pwd, 126);
	builtin_setenv(info, "OLDPWD", old_pwd);
	chdir(new_pwd);
	getcwd(pwd, 126);
	builtin_setenv(info, "PWD", pwd);
}

int		builtin_cd(t_data *info)
{
	if (!info->av[1][0] || info->av[1][0] == '~')
	{
		if (!replace_tild(info))
			return (print_error(6));
	}
	else if (!(ft_strcmp(info->av[1], "-")))
		if (!replace_minus(info))
			return (print_error(7));
	change_current_dir(info, info->av[1]);
	return (1);
}

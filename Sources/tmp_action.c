#include "../Includes/shell.h"

void	tmp_action(t_data *info)
{
	if (!(ft_strcmp(info->av[0], "env")))
		builtin_env(info);
	else if (!(ft_strcmp(info->av[0], "setenv")))
		builtin_setenv(info, info->av[1], info->av[2]);
	else if (!(ft_strcmp(info->av[0], "unsetenv")))
		builtin_unsetenv(info);
}

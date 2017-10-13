#include "../Includes/shell.h"

/*static int	replace_tild(t_data *info)
{
	t_list	*home;
	char	*tild;

	home = ft_get_p_elem(info->env_list, check_var(info->env_list, "HOME"));
	if (!home)
		return (0);
	tild = ((t_env*)(home->data))->env_value;
	ft_bzero(info->av[1], 100);
	ft_strcpy(info->av[1], tild);
	return (1);
}*/

int		check_path_error(t_data *info, char *path)
{
	(void)info;
	(void)path;
	return (0);
}

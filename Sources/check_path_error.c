/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 23:16:26 by proso             #+#    #+#             */
/*   Updated: 2017/11/24 05:07:52 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int		print_path_error(char p_e_d[3], char *path, int print, int type)
{
	if (type == 1)
		ft_putstr_color("cd: ", C_RED);
	if (p_e_d[1] == 'B' && print)
	{
		if (!type)
			ft_putstr_color("21sh: ", C_RED);
		ft_printf("{bold}{red}No such file or directory: %s{res}\n", path);
	}
	else if (p_e_d[2] == 'B' && print && type)
		ft_printf("{bold}{red}Not a directory: %s{res}\n", path);
	else if (p_e_d[0] == 'B' && print)
	{
		if (!type)
			ft_putstr_color("21sh: ", C_RED);
		ft_printf("{bold}{red}Permission denied: %s{res}\n", path);
	}
	return ((type) ? -1 : 1);
}

static void		check_access(char p_e_d[3], char *tmp, struct stat buf)
{
	p_e_d[0] = (access(tmp, X_OK) == -1) ? 'B' : 'A';
	p_e_d[1] = (access(tmp, F_OK) == -1) ? 'B' : 'A';
	p_e_d[2] = ((buf.st_mode & S_IFMT) != S_IFDIR) ? 'B' : 'A';
}

int				check_path_error(char *path, int allow_print, int type)
{
	int			i;
	struct stat	buf;
	char		p_e_d[3];
	char		*tmp;

	tmp = ft_strdup(path);
	ft_memset(p_e_d, 'A', 3);
	i = (path[0] == '/') ? 1 : 0;
	while (path[i])
	{
		while (path[i] && path[i] != '/')
			i++;
		tmp[i] = '\0';
		lstat(tmp, &buf);
		check_access(p_e_d, tmp, buf);
		if (p_e_d[0] == 'B' || p_e_d[1] == 'B' || p_e_d[2] == 'B')
		{
			ft_strdel(&tmp);
			return (print_path_error(p_e_d, path, allow_print, type));
		}
		tmp[i++] = '/';
	}
	ft_strdel(&tmp);
	return (1);
}

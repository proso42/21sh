/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 23:16:26 by proso             #+#    #+#             */
/*   Updated: 2017/10/16 02:33:38 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void		print_path_error(char p_e_d[3], char *path)
{
	if (p_e_d[1] == 'B')
		ft_printf("\n{bold}{red}cd: No such file or directory: %s{res}", path);
	else if (p_e_d[2] == 'B')
		ft_printf("\n{bold}{red}cd: Not a directory: %s{res}", path);
	else if (p_e_d[0] == 'B')
		ft_printf("\n{bold}{red}cd: Permission denied: %s{res}", path);
}

int				check_path_error(char *path)
{
	int			i;
	struct stat	buf;
	char		p_e_d[3];
	char		tmp[ft_strlen(path)];

	ft_strcpy(tmp, path);
	ft_memset(p_e_d, 'A', 3);
	i = (path[0] == '/') ? 1 : 0;
	while (path[i])
	{
		while (path[i] && path[i] != '/')
			i++;
		tmp[i] = '\0';
		lstat(tmp, &buf);
		p_e_d[0] = (access(tmp, X_OK) == -1) ? 'B' : 'A';
		p_e_d[1] = (access(tmp, F_OK) == -1) ? 'B' : 'A';
		p_e_d[2] = ((buf.st_mode & S_IFMT) != S_IFDIR) ? 'B' : 'A';
		if (p_e_d[0] == 'B' || p_e_d[1] == 'B' || p_e_d[2] == 'B')
		{
			print_path_error(p_e_d, path);
			return (-1);
		}
		tmp[i++] = '/';
	}
	return (1);
}

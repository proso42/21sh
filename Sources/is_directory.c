/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 02:38:58 by proso             #+#    #+#             */
/*   Updated: 2017/11/12 02:40:04 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int		is_directory(char *path)
{
	struct stat	buf;

	lstat(path, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_printf("{bold}{red}21sh: %s is a directory !{res}\n", path);
		return (1);
	}
	return (0);
}

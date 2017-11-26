/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_local_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 01:44:43 by proso             #+#    #+#             */
/*   Updated: 2017/11/27 00:38:16 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

char	*check_local_path(char *path)
{
	int		i;
	int		ok;

	i = (path[1] == '/') ? 2 : 1;
	ok = 0;
	if (path[i] == '/')
	{
		path[i] = '\0';
		ok = 1;
	}
	if (check_path_error(path, 1, 0) < 0)
		return (NULL);
	if (is_directory(path))
		return (NULL);
	if (ok)
		path[i] = '/';
	return (ft_strdup(path));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 23:55:07 by proso             #+#    #+#             */
/*   Updated: 2017/11/12 20:56:26 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int		search_exe(char *path, char *exe)
{
	DIR				*dirp;
	struct dirent	*buf;

	if (!(dirp = opendir(path)))
		return (0);
	buf = readdir(dirp);
	while (buf)
	{
		if (!(ft_strcmp(exe, buf->d_name)))
		{
			closedir(dirp);
			return (1);
		}
		buf = readdir(dirp);
	}
	closedir(dirp);
	return (0);
}

char	*get_next_path(int *i, int *j, char *env_path)
{
	*j = *i;
	while (env_path[*i] && env_path[*i] != ':')
		(*i)++;
	return (ft_strsub(env_path, *j, *i - *j));
}

char	*check_relative_path(t_data *info, char *path)
{
	char	*env_path;
	char	*tmp;
	int		i;
	int		j;

	if (!(env_path = get_env_var(info, "PATH")))
	{
		print_error(6);
		return (NULL);
	}
	i = 0;
	while (env_path[i++])
	{
		tmp = get_next_path(&i, &j, env_path);
		if (search_exe(tmp, path))
		{
			env_path = ft_strjoin(tmp, "/");
			env_path = ft_strjoinfree(env_path, path, 1);
			ft_strdel(&tmp);
			return (env_path);
		}
		ft_strdel(&tmp);
	}
	ft_printf("{bold}{red}21sh: command not found: %s{res}\n", path);
	return (NULL);
}

char	*check_absolute_path(char *path)
{
	char	*exe;
	int		i;
	int		ret;

	if (check_path_error(path, 1, 0) < 0)
		return (NULL);
	else if (is_directory(path))
		return (NULL);
	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	exe = ft_strsub(path, i + 1, ft_strlen(path));
	path[i] = '\0';
	ret = search_exe(path, exe);
	ft_strdel(&exe);
	path[i] = '/';
	return (ft_strdup(path));
}

char	*find_cmd(t_data *info, char *path)
{
	char	*rep;

	if (!path)
		return (NULL);
	else if (path[0] == '/')
		rep = check_absolute_path(path);
	else if (path[0] == '.')
		rep = check_local_path(path);
	else
		rep = check_relative_path(info, path);
	return (rep);
}

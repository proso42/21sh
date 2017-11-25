/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:04:23 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 01:42:03 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int	is_bad_char(char c)
{
	return (c != '_' && !ft_isdigit(c) && !ft_isalpha(c));
}

static int	check_wrong_dol(int *i, char *arg)
{
	if (is_bad_char(arg[*i + 1]) && arg[*i + 1] != '$')
		return (1);
	else if (arg[*i + 1] == '$')
		return (2);
	return (0);
}

static char	*analyse_dollard(t_data *info, char *arg, int *i)
{
	int		j;
	char	*tmp;
	char	*dol;

	tmp = NULL;
	j = check_wrong_dol(i, arg);
	if (j == 2)
	{
		(*i) += 2;
		return (ft_itoa(getpid()));
	}
	else if (j == 1)
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	(*i)++;
	j = *i;
	while (arg[*i] && !(is_bad_char(arg[*i])))
		(*i)++;
	if (*i - j != 0)
		tmp = ft_strsub(arg, j, *i - j);
	dol = get_env_var(info, tmp);
	ft_strdel(&tmp);
	return ((dol) ? ft_strdup(dol) : NULL);
}

static void	loop(char *str, char **tmp, int *i, t_data *info)
{
	char	*env_var;
	int		sg_quote;
	int		db_quote;

	ft_init(0, 2, &sg_quote, &db_quote);
	while (str[*i])
	{
		if (str[*i] == '$' && !sg_quote)
		{
			env_var = analyse_dollard(info, str, i);
			if (env_var)
				*tmp = ft_strjoinfree(*tmp, env_var, 3);
		}
		else
		{
			if (str[*i] == '\'' && !db_quote)
				sg_quote = (sg_quote) ? 0 : 1;
			else if (str[*i] == '\"' && !sg_quote)
				db_quote = (db_quote) ? 0 : 1;
			ft_strncat(*tmp, &str[*i], 1);
			(*i)++;
		}
	}
}

void		replace_dollard(t_data *info, char **str)
{
	int		i;
	char	*tmp;
	char	*env_var;

	i = 0;
	env_var = NULL;
	tmp = ft_strnew(info->size_max);
	loop(*str, &tmp, &i, info);
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
	if (!*str[0])
		*str[0] = -1;
}

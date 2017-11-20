/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:04:23 by proso             #+#    #+#             */
/*   Updated: 2017/11/21 00:41:56 by proso            ###   ########.fr       */
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

static void	loop(char str[], char tmp[], int *i, t_data *info)
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
			{
				ft_strlcpy(&tmp[ft_strlen(tmp)], env_var, 1024);
				ft_strdel(&env_var);
			}
		}
		else
		{
			if (str[*i] == '\'' && !db_quote)
				sg_quote = (sg_quote) ? 0 : 1;
			else if (str[*i] == '\"' && !sg_quote)
				db_quote = (db_quote) ? 0 : 1;
			tmp[ft_strlen(tmp)] = str[(*i)++];
		}
	}
}

void		replace_dollard(t_data *info, char str[])
{
	int		i;
	char	tmp[1024];
	char	*env_var;

	i = 0;
	env_var = NULL;
	ft_bzero(tmp, 1024);
	loop(str, tmp, &i, info);
	ft_bzero(str, 1024);
	ft_strncpy(str, tmp, 1023);
	if (!str[0])
		str[0] = -1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 11:14:23 by proso             #+#    #+#             */
/*   Updated: 2017/06/17 11:14:25 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void	pass_space(char *str, int *i)
{
	while (str[*i] == ' ' && str[*i])
		(*i)++;
}

static void	pick_part(t_data *info, int *i, int *j)
{
	int		sg_quote;
	int		db_quote;
	int		k;
	char	*str;

	sg_quote = 0;
	db_quote = 0;
	k = 0;
	str = info->buf_cmd;
	ft_bzero(info->av[*j], 100);
	while ((str[*i] != ' ' || (str[*i] == ' ' && (sg_quote || db_quote)))
																	&& str[*i])
	{
		if (str[*i] == '\"' && !sg_quote)
			db_quote = (db_quote) ? 0 : 1;
		else if (str[*i] == '\'' && !db_quote)
			sg_quote = (sg_quote) ? 0 : 1;
		if (str[*i] != ' ' || (str[*i] == ' ' && (sg_quote || db_quote)))
			info->av[*j][k++] = str[*i];
		(*i)++;
	}
}

int			cut_cmd(t_data *info)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (info->buf_cmd[i])
	{
		pass_space(info->buf_cmd, &i);
		pick_part(info, &i, &j);
		j++;
	}
	ft_bzero(info->av[j], 100);
	j = 0;
	while (info->av[j][0])
	{
		if (ft_strchr(info->av[j], '$'))
			replace_dollard(info, info->av[j]);
		j++;
	}
	return (0);
}

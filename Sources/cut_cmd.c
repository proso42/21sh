/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 11:14:23 by proso             #+#    #+#             */
/*   Updated: 2017/10/21 05:57:51 by caroleroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void	remove_useless_symbol(t_data *info, int j)
{
	char	*tmp;
	int		sg_quote;
	int		db_quote;
	int		i;

	ft_init(0, 3, &i, &sg_quote, &db_quote);
	while (info->av[j][i])
	{
		if (info->av[j][i] == '\'' && !db_quote)
		{
			sg_quote = (sg_quote) ? 0 : 1;
			info->av[j][i] = 1;
		}
		else if (info->av[j][i] == '\"' && !sg_quote)
		{
			db_quote = (db_quote) ? 0 : 1;
			info->av[j][i] = 1;
		}
		i++;
	}
	tmp = ft_strnew(100);
	ft_strcpy(tmp, info->av[j]);
	tmp = ft_str_remove_c(tmp, 1);
	ft_strcpy(info->av[j], tmp);
	ft_strdel(&tmp);
}

static void	clean_cmd(t_data *info)
{
	int		j;

	j = 0;
	while (info->av[j][0])
	{
		if (ft_strchr(info->av[j], '$'))
			replace_dollard(info, info->av[j]);
		j++;
	}
	j = 0;
	while (info->av[j][0])
	{
		if (ft_strchr(info->av[j], '\'') || ft_strchr(info->av[j], '\"'))
			remove_useless_symbol(info, j);
		j++;
	}
}

static void	add_operand(t_data *info, int *i, int *j)
{
	char	*c;

	c = &info->buf_cmd[*i];
	if (info->av[*j][0])
		(*j)++;
	if (c[0] == '>' && c[1] == '>')
		ft_memset(info->av[*j], '>', 2);
	else if (c[0] == '<' && c[1] == '<')
		ft_memset(info->av[*j], '<', 2);
	else if (c[0] == '&' && c[1] == '&')
		ft_memset(info->av[*j], '&', 2);
	else if (c[0] == '|' && c[1] == '|')
		ft_memset(info->av[*j], '|', 2);
	else if ((c[0] == '<') || c[0] == '>' || c[0] == '|' || c[0] == ';'
																|| c[0] == '&')
		info->av[*j][0] = c[0];
	*i = (info->av[*j][1]) ? (*i) + 2 : (*i) + 1;
}

static void	pick_part(t_data *info, int *i, int *j)
{
	int		qu;
	int		db_qu;
	int		k;

	ft_init(0, 3, &k, &qu, &db_qu);
	while (info->buf_cmd[*i])
	{
		if (info->buf_cmd[*i] == 39 && !db_qu)
			qu = (qu) ? 0 : 1;
		else if (info->buf_cmd[*i] == 34 && !qu)
			db_qu = (db_qu) ? 0 : 1;
		if ((info->buf_cmd[*i] == ' ' && !db_qu && !qu) || !info->buf_cmd[*i])
			return ;
		else if (!qu && !db_qu && is_operand(&info->buf_cmd[*i]))
		{
			add_operand(info, i, j);
			return ;
		}
		else
		{
			info->av[*j][k++] = info->buf_cmd[*i];
			(*i)++;
		}
	}
}

int			cut_cmd(t_data *info)
{
	int		i;
	int		j;

	ft_init(0, 2, &i, &j);
	if (!info->buf_cmd[0])
		return (0);
	while (info->buf_cmd[i])
	{
		while (info->buf_cmd[i] && info->buf_cmd[i] == ' ')
			i++;
		pick_part(info, &i, &j);
		j++;
	}
	ft_bzero(info->av[j], 100);
	j = 0;
	while (info->av[j][0])
		j++;
	if (j > 0)
		j--;
	eval_quote(info, j);
	clean_cmd(info);
	if ((init_line_edition(info)) < 0)
		exit(-1);
	if (info->pid == -4)
	{
		info->pid = 0;
		return (1);
	}
	return (0);
}

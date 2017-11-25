/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 11:14:23 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 01:41:41 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"
#include <string.h>

static void	remove_useless_symbol(t_data *info, int j)
{
	char	*tmp;
	int		sg_quote;
	int		db_quote;
	int		i;
	int		k;

	ft_init(0, 4, &i, &k, &sg_quote, &db_quote);
	tmp = ft_strnew(info->size_max);
	while (info->av[j][i])
	{
		if (info->av[j][i] == '\'' && !db_quote)
			sg_quote = (sg_quote) ? 0 : 1;
		else if (info->av[j][i] == '\"' && !sg_quote)
			db_quote = (db_quote) ? 0 : 1;
		if (info->av[j][i] == '\'' && db_quote)
			tmp[k++] = info->av[j][i];
		else if (info->av[j][i] == '\"' && sg_quote)
			tmp[k++] = info->av[j][i];
		else if (info->av[j][i] != '\'' && info->av[j][i] != '\"')
			tmp[k++] = info->av[j][i];
		i++;
	}
	ft_bzero(info->av[j], ft_strlen(info->av[j]));
	ft_strlcpy(info->av[j], tmp, info->size_max);
	ft_strdel(&tmp);
}

static int	clean_cmd(t_data *info)
{
	int		j;

	j = 0;
	while (info->av[j] && info->av[j][0])
	{
		if (ft_strchr(info->av[j], '$'))
			replace_dollard(info, &info->av[j]);
		j++;
	}
	j = 0;
	while (info->av[j] && info->av[j][0])
	{
		if (ft_strchr(info->av[j], '\'') || ft_strchr(info->av[j], '\"'))
			remove_useless_symbol(info, j);
		j++;
	}
	if (info->pid == -4)
	{
		info->pid = 0;
		if ((init_line_edition(info)) < 0)
			exit(-1);
		return (1);
	}
	return (0);
}

static void	add_operand(t_data *info, int *i, int k)
{
	char	str[3];

	ft_bzero(str, 3);
	info->tmp_buf = ft_strsub(info->buf_cmd, k, (*i) - k - 1);
	ft_push_array(info->av, info->tmp_buf, info->size_max);
	ft_strdel(&info->tmp_buf);
	str[0] = info->buf_cmd[*i];
	str[1] = info->buf_cmd[*i + 1];
	if (str[0] == '>' && str[1] == '>')
		ft_push_array(info->av, ">>", 1024);
	else if (str[0] == '<' && str[1] == '<')
		ft_push_array(info->av, "<<", 1024);
	else if (str[0] == '&' && str[1] == '&')
		ft_push_array(info->av, "&&", 1024);
	else if (str[0] == '|' && str[1] == '|')
		ft_push_array(info->av, "||", 1024);
	else if ((str[0] == '<') || str[0] == '>' || str[0] == '|' || str[0] == ';'
															|| str[0] == '&')
	{
		str[1] = '\0';
		ft_push_array(info->av, str, info->size_max);
	}
	(*i)++;
}

static void	pick_part(t_data *info, int *i)
{
	int		qu;
	int		db_qu;
	int		k;

	ft_init(0, 2, &qu, &db_qu);
	k = *i;
	while (1)
	{
		if (info->buf_cmd[*i] == 39 && !db_qu)
			qu = (qu) ? 0 : 1;
		else if (info->buf_cmd[*i] == 34 && !qu)
			db_qu = (db_qu) ? 0 : 1;
		if ((info->buf_cmd[*i] == ' ' && !db_qu && !qu) || !info->buf_cmd[*i])
		{
			info->tmp_buf = ft_strsub(info->buf_cmd, k, (*i) - k);
			ft_push_array(info->av, info->tmp_buf, info->size_max);
			ft_strdel(&info->tmp_buf);
			return ;
		}
		else if (!qu && !db_qu && is_operand(&info->buf_cmd[*i]))
			return (add_operand(info, i, k));
		else
			(*i)++;
	}
}

int			cut_cmd(t_data *info)
{
	int		i;

	i = 0;
	if (!info->buf_cmd[0])
		return (0);
	while (info->buf_cmd[i])
	{
		while (info->buf_cmd[i] && info->buf_cmd[i] == ' ')
			i++;
		pick_part(info, &i);
	}
	eval_quote(info, 0);
	add_cmd_to_history(info);
	if (clean_cmd(info))
		return (1);
	if ((init_line_edition(info)) < 0)
		exit(-1);
	return (0);
}

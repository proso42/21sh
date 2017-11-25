/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 11:14:23 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 03:51:38 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"
#include <string.h>

static void	intern_loop(char *tmp, char *tmp2)
{
	int		sg_quote;
	int		db_quote;
	int		k;
	int		i;

	ft_init(0, 4, &i, &k, &sg_quote, &db_quote);
	while (tmp[i])
	{
		if (tmp[i] == '\'' && !db_quote)
			sg_quote = (sg_quote) ? 0 : 1;
		else if (tmp[i] == '\"' && !sg_quote)
			db_quote = (db_quote) ? 0 : 1;
		if (tmp[i] == '\'' && db_quote)
			tmp2[k++] = tmp[i];
		else if (tmp[i] == '\"' && sg_quote)
			tmp2[k++] = tmp[i];
		else if (tmp[i] != '\'' && tmp[i] != '\"')
			tmp2[k++] = tmp[i];
		i++;
	}
}

static void	remove_useless_symbol(t_data *info, int j)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(info->av[j]);
	tmp2 = ft_strnew(ft_strlen(tmp));
	intern_loop(tmp, tmp2);
	ft_strdel_var(2, &info->av[j], &tmp);
	*(&info->av[j]) = ft_strdup(tmp2);
	ft_strdel(&tmp2);
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

static void	add_operand(t_data *info, int *i, int j)
{
	char	str[3];

	ft_bzero(str, 3);
	if (info->tmp_buf)
		ft_strdel(&info->tmp_buf);
	info->tmp_buf = ft_strsub(info->buf_cmd, j, (*i) - j - 1);
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

static void	pick_part(t_data *info, int *i, int j)
{
	int		sg_qu;
	int		db_qu;
	char	*tmp;

	ft_init(0, 2, &sg_qu, &db_qu);
	while (info->buf_cmd[*i])
	{
		if (info->buf_cmd[*i] == '\'')
			sg_qu = (!sg_qu && !db_qu) ? 1 : 0;
		else if (info->buf_cmd[*i] == '\"')
			db_qu = (!db_qu && !sg_qu) ? 1 : 0;
		if (info->buf_cmd[*i] == ' ' && !db_qu && !sg_qu)
			break;
		else if ((info->buf_cmd[*i] == ';' || info->buf_cmd[*i] == '<' ||
						info->buf_cmd[*i] == '>' || info->buf_cmd[*i] == '&' ||
								info->buf_cmd[*i] == '|') && !db_qu && !sg_qu)
			return (add_operand(info, i, j));
		else
			(*i)++;
	}
	tmp = ft_strsub(info->buf_cmd, j, (*i) - j);
	ft_push_array(info->av, tmp, info->size_max);
	ft_strdel(&tmp);
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
		j = i;
		pick_part(info, &i, j);
	}
	eval_quote(info, 0);
	add_cmd_to_history(info);
	if (clean_cmd(info))
		return (1);
	if ((init_line_edition(info)) < 0)
		exit(-1);
	return (0);
}

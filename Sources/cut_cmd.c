/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 11:14:23 by proso             #+#    #+#             */
/*   Updated: 2017/10/16 03:41:41 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void	pass_space(char *str, int *i)
{
	while (str[*i] == ' ' && str[*i])
		(*i)++;
}

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
	ft_bzero(info->av[j], 100);
	tmp = ft_str_remove_c(tmp, 1);
	ft_strcpy(info->av[j], tmp);
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

static void pick_part(t_data *info, int *i, int *j)
{
	int		quote;
	int		db_quote;
	int		k;

	ft_init(0, 3, &k, &quote, &db_quote);
	while (info->buf_cmd[*i])
	{
		if (info->buf_cmd[*i] == 39 && !db_quote)
			quote = (quote) ? 0 : 1;
		else if (info->buf_cmd[*i] == 34 && !quote)
			db_quote = (db_quote) ? 0 : 1;
		if ((info->buf_cmd[*i] == ' ' && !db_quote && !quote)
														|| !info->buf_cmd[*i])
			return;
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
		pass_space(info->buf_cmd, &i);
	//	ft_bzero(info->av[j], 100);
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
	//term_action(info, "do");
	//default_terminal(info, 0);
	//lexer_parser(info);
	if ((init_line_edition(info)) < 0)
		exit(-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 13:44:57 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 01:41:28 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void	recursive_quote(t_data *info, int j)
{
	int		ret;

	ft_bzero(info->buf_cmd, info->size_max);
	info->buf_i = 0;
	term_action(info, "do");
	print_prompt(info);
	while (info->quote > 0)
	{
		if ((ret = get_stdin(info)) == 18)
		{
			info->av[j][ft_strlen(info->av[j])] = '\n';
			info->av[j] = ft_strjoinfree(info->av[j], info->buf_cmd, 1);
			ft_bzero(info->buf_cmd, info->size_max);
			info->buf_i = 0;
			info->quote = 0;
		}
	}
	eval_quote(info, j);
}

void		eval_quote(t_data *info, int j)
{
	int		i;
	int		sg_quote;
	int		db_quote;

	ft_init(0, 3, &i, &sg_quote, &db_quote);
	while (info->av[j][i])
	{
		if (info->av[j][i] == '\'' && !db_quote)
			sg_quote = (sg_quote) ? 0 : 1;
		else if (info->av[j][i] == '\"' && !sg_quote)
			db_quote = (db_quote) ? 0 : 1;
		i++;
	}
	if (sg_quote)
		info->quote = 1;
	else if (db_quote)
		info->quote = 2;
	if (info->quote)
		recursive_quote(info, j);
}

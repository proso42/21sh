/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 21:42:40 by proso             #+#    #+#             */
/*   Updated: 2017/11/26 20:57:08 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void	save_buf(t_data *info)
{
	char	*tmp;

	if (info->save_buf == NULL)
		info->save_buf = ft_strjoin(info->buf_cmd, "\n");
	else
	{
		tmp = ft_strdup(info->save_buf);
		ft_strdel(&info->save_buf);
		info->save_buf = ft_strjoin_var(3, tmp, info->buf_cmd, "\n");
		ft_strdel(&tmp);
	}
}

static void	update_quote(t_data *info, char c)
{
	if (c == '\'' && info->quote == 1)
		info->quote = 0;
	else if (c == '\"' && info->quote == 2)
		info->quote = 0;
	else if (c == '\'' && info->quote == 0)
		info->quote = 1;
	else if (c == '\"' && info->quote == 0)
		info->quote = 2;
}

int			test_quote(t_data *info)
{
	int		i;

	i = 0;
	while (info->buf_cmd[i])
		update_quote(info, info->buf_cmd[i++]);
	if (info->quote)
		save_buf(info);
	if (!info->quote && info->save_buf)
	{
		info->buf_cmd = ft_strjoinfree(info->save_buf, info->buf_cmd, 2);
		ft_strdel(&info->save_buf);
	}
	return (0);
}

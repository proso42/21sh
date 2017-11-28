/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_useless_symbol.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 00:53:11 by proso             #+#    #+#             */
/*   Updated: 2017/11/28 23:13:03 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

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

void	remove_useless_symbol(char **str)
{
	char	*tmp;
	char	*tmp2;

	if (!ft_strchr(*str, '\'') && !ft_strchr(*str, '\"'))
		return ;
	tmp = ft_strdup(*str);
	tmp2 = ft_strnew(ft_strlen(tmp));
	intern_loop(tmp, tmp2);
	ft_strdel_var(2, str, &tmp);
	*str = ft_strdup(tmp2);
	ft_strdel(&tmp2);
}

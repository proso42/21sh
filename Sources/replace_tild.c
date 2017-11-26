/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tild.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 00:24:14 by proso             #+#    #+#             */
/*   Updated: 2017/11/26 21:14:39 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void	update_tmp(t_data *info, char **tmp, int i, int *j)
{
	char	*tmp2;

	tmp2 = ft_strsub(info->tmp_buf, *j, i - (*j));
	*tmp = ft_strjoinfree(*tmp, tmp2, 3);
	tmp2 = get_env_var(info, "HOME");
	if (tmp2)
		*tmp = ft_strjoinfree(*tmp, tmp2, 1);
	*j = i + 1;
}

static void	update_str(char **tmp, char **str)
{
	ft_strdel(str);
	*str = ft_strdup(*tmp);
	ft_strdel(tmp);
}

void		replace_tild(t_data *info, char **str)
{
	int		i;
	int		j;
	int		db_quote;
	int		sg_quote;
	char	*tmp;

	if (!ft_strchr(*str, '~'))
		return ;
	tmp = NULL;
	info->tmp_buf = *str;
	ft_init(0, 2, &i, &j);
	sg_quote = ((*str)[i] == '\'') ? 1 : 0;
	db_quote = ((*str)[i] == '\"') ? 1 : 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '~' && !sg_quote && !db_quote)
			update_tmp(info, &tmp, i, &j);
		i++;
		if ((*str)[i] == '\'' && !db_quote)
			sg_quote = (!sg_quote) ? 1 : 0;
		else if ((*str)[i] == '\"' && !db_quote)
			db_quote = (!db_quote) ? 1 : 0;
	}
	if (tmp)
		update_str(&tmp, &info->tmp_buf);
}

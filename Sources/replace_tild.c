/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tild.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 00:24:14 by proso             #+#    #+#             */
/*   Updated: 2017/11/28 23:28:09 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

void		replace_tild(t_data *info, char **str)
{
	char	*home;
	char	*tmp;

	if ((*str)[0] != '~')
		return ;
	if (!(home = get_env_var(info, "HOME")))
		return ;
	tmp = ft_strjoin(home, *str + 1);
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
}

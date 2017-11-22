/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   past_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 00:10:30 by proso             #+#    #+#             */
/*   Updated: 2017/11/22 02:48:08 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int		past_mode(t_data *info)
{
	int		i;
	char	tmp[1024];

	if (!info->cpy || !info->cpy[0] || (int)ft_strlen(info->cpy) +
										(int)ft_strlen(info->buf_cmd) > 1023)
		return (0);
	i = 0;
	ft_bzero(tmp, 1024);
	while (i < info->buf_i)
	{
		tmp[i] = info->buf_cmd[i];
		i++;
	}
	ft_strlcpy(&(tmp[i]), info->cpy, 1024 - i);
	ft_strlcpy(&(tmp[ft_strlen(tmp)]), &(info->buf_cmd[i]), 1024 - ft_strlen(tmp));
	home(info, 1);
	ft_bzero(info->buf_cmd, 1024);
	ft_strlcpy(info->buf_cmd, tmp, 1024);
	write_buf(info);
	info->buf_i = ft_strlen(info->buf_cmd);
	return (0);
}

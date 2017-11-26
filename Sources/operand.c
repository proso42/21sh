/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 23:26:09 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 23:50:31 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int	is_operand(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	get_operand(char *str, int i)
{
	if (str[i] && str[i] == '|' && str[i + 1] == '|')
		return (OR);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] && str[i] == '&' && str[i + 1] == '&')
		return (AND);
	else if (str[i] == '&')
		return (AGREG);
	else if (str[i] == ';')
		return (SEMICOLON);
	else if (str[i] && str[i] == '>' && str[i + 1] == '>')
		return (REDIR_RR);
	else if (str[i] == '>')
		return (REDIR_R);
	else if (str[i] && str[i] == '<' && str[i + 1] == '<')
		return (REDIR_LL);
	else if (str[i] == '<')
		return (REDIR_L);
	return (BK);
}

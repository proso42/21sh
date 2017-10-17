/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:09:17 by proso             #+#    #+#             */
/*   Updated: 2017/10/18 00:07:06 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int	get_op(t_data *info, char **cmd)
{
	int		i;

	i = 0;
	while (info->av[i][0] && ft_strcmp(info->av[i], cmd[i]))
		i++;
	i = 0;
	if (!cmd[i][0])
		return (0);
	else if (cmd[i][0] == '<' && !cmd[i][1])
		return (REDIR_L);
	else if (cmd[i][0] == '>' && !cmd[i][1])
		return (REDIR_R);
	else if (cmd[i][0] == '|' && !cmd[i][1])
		return (PIPE);
	else if (cmd[i][0] == ';' && !cmd[i][1])
		return (SEMICOLON);
	else if (cmd[i][0] == '<' && cmd[i][1] == '<' && !cmd[i][2])
		return (REDIR_LL);
	else if (cmd[i][0] == '>' && cmd[i][1] == '>' && !cmd[i][2])
		return (REDIR_RR);
	else if (cmd[i][0] == '|' && cmd[i][1] == '|' && !cmd[i][2])
		return (OR);
	else if (cmd[i][0] == '&' && cmd[i][1] == '&' && !cmd[i][2])
		return (AND);
	return (0);
}

static int	cmp_lexem(void *item1, void *item2)
{
	return ((((t_lexem*)(item1))->prty >= ((t_lexem*)(item2))->prty) ? 1 : 0);
}

void		add_lexem(char **cmd, int bk, int prty, t_data *info)
{
	t_lexem	*lexem;

	if (!(lexem = (t_lexem*)malloc(sizeof(t_lexem))))
	{
		print_error(ERR_MALLOC);
		exit(-1);
	}
	lexem->cmd = cmd;
	lexem->bk = bk;
	lexem->prty = prty;
	lexem->op = get_op(info, cmd);
	btree_insert_data(&info->root, lexem, cmp_lexem);
}

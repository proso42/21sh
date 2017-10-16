/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 14:40:35 by proso             #+#    #+#             */
/*   Updated: 2017/10/16 03:03:24 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int			is_operand(char *c)
{
	if ((c[0] == '>' && c[1] == '>' && !c[2]) || (c[0] == '<' && c[1] == '<'
																	&& !c[2]))
		return (1);
	else if ((c[0] == '&' && c[1] == '&' && !c[2]) || (c[0] == '|'
													&& c[1] == '|' && !c[2]))
		return (1);
	else if ((c[0] == '<' || c[0] == '>' || c[0] == '|' || c[0] == ';')
																	&& !c[1])
		return (1);
	return (0);
}

static int	get_priority(char *c)
{
	if ((c[0] == '>' && !c[1]) || (c[0] == '<' && !c[1]) ||
		(c[0] == '|' && !c[1]) || (c[0] == '>' && c[1] == '>' && !c[2]) ||
		(c[0] == '<' && c[1] == '<' && !c[2]))
		return (-1);
	else if ((c[0] == ';' && !c[1]) || (c[0] == '|' && c[1] == '|' && !c[2]) ||
		(c[0] == '&' && c[1] == '&' && !c[2]))
		return (1);
	else if (!c[0])
		return (0);
	return (0);
}

static char	**create_tab(int i, int j, int *bk, t_data *info)
{
	char	**cmd;
	int		k;

	k = 0;
	if (!(cmd = (char**)malloc(sizeof(char*) * (i + 1))))
	{
		print_error(ERR_MALLOC);
		exit(-1);
	}
	while (j++ < i)
		if (info->av[j][0] == '&' && !info->av[j][1])
			*bk = 1;
		else
		{
			cmd[k] = ft_strdup(info->av[j]);
			k++;
		}
	cmd[j] = NULL;
	return (cmd);
}

void		lexer(t_data *info)
{
	int		i;
	int		j;
	int		bk;
	int		prty;
	char	**cmd;

	ft_init(0, 4, &i, &j, &bk, &prty);
	cmd = NULL;
	while (info->av[i][0])
	{
		if (is_operand(info->av[i]))
		{
			cmd = create_tab(i, j, &bk, info);
			prty = get_priority(info->av[j]);
			add_lexem(cmd, bk, prty, info);
			j = i + 1;
		}
		i++;
	}
	if (!cmd)
	{
		cmd = create_tab(i, j, &bk, info);
		add_lexem(cmd, bk, prty, info);
	}
}

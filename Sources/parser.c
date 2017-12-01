/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 22:16:31 by proso             #+#    #+#             */
/*   Updated: 2017/12/01 02:21:54 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"
#define DATA ((t_lexem*)(current->data))

int		start_with_operand(char *str)
{
	if ((str[0] == '|' || str[0] == '&') && !str[1])
		ft_printf("{bold}{red}21sh: parse error near `%c'{res}\n", str[0]);
	else if (str[0] == '|' && str[1] == '|')
		ft_printf("{bold}{red}21sh: parse error near `||'{res}\n");
	else if (str[0] == '&' && str[1] == '&')
		ft_printf("{bold}{red}21sh: parse error near `&&'{res}\n");
	else if (str[0] == ';' && str[1] == ';')
		ft_printf("{bold}{red}21sh: parse error near `;;'{res}\n");
	else if (str[0] == ';')
		ft_printf("{bold}{red}21sh: parse error near `;'{res}\n");
	else if (str[0] == '>' || str[0] == '<')
		ft_printf("{bold}{red}21sh: parse error near `\\n'{res}\n");
	else
		return (0);
	return (1);
}

static t_list	*leave_op(t_list *list, int op)
{
	t_list *current;

	current = list;
	while (current && DATA->op == op)
		current = current->next;
	return (current) ? current->next : NULL;
}

static t_list	*run_and_or(t_data *info, t_list *list)
{
	int		and;
	int		or;
	int		ret;
	t_list	*current;

	current = list;
	and = (DATA->op == AND) ? 1 : 0;
	or = (DATA->op == OR) ? 1 : 0;
	ret = exectute(info, DATA);
	if (!ret && and)
		return (leave_op(current, AND));
	else if ((ret && and) || (!ret && or))
		return (current->next);
	else
		return (leave_op(current, OR));
}

void	parser(t_data *info)
{
	t_list	*current;

	current = info->lexem_list;
	while (current)
	{
		if (DATA->op == SEMICOLON && DATA->cmd)
		{
			exectute(info, DATA);
			current = current->next;
		}
		else if ((DATA->op == AND || DATA->op == OR) && DATA->cmd)
			current = run_and_or(info, current);
		else if (DATA->op == SEMICOLON && !DATA->cmd)
			current = current->next;
		else if (DATA->op == BK && DATA->cmd)
		{
			exectute(info, DATA);
			return ;
		}
		else if (DATA->op == BK && !DATA->cmd)
			return ;
	}
}

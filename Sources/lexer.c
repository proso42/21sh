/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 14:40:35 by proso             #+#    #+#             */
/*   Updated: 2017/11/05 03:06:18 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int			is_operand(char *c)
{
	if ((c[0] == '>' && c[1] == '>' && !c[2]) || (c[0] == '<' && c[1] == '<'))
		return (1);
	else if ((c[0] == '&' && c[1] == '&' && !c[2]) || (c[0] == '|'
																&& c[1] == '|'))
		return (1);
	else if ((c[0] == '<' || c[0] == '>' || c[0] == '|' || c[0] == ';'
																|| c[0] == '&'))
		return (1);
	return (0);
}

static int			set_operand(char *str)
{
	if (!ft_strcmp(str, "||"))
		return (OR);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if (!ft_strcmp(str, "&&"))
		return (AND);
	else if (!ft_strcmp(str, "&"))
		return (AGREG);
	else if (!ft_strcmp(str, ";"))
		return (SEMICOLON);
	else if (!ft_strcmp(str, ">>"))
		return (REDIR_RR);
	else if (!ft_strcmp(str, ">"))
		return (REDIR_R);
	else if (!ft_strcmp(str, "<<"))
		return (REDIR_LL);
	else if (!ft_strcmp(str, "<"))
		return (REDIR_L);
	return (BK);
}

/*static int	is_builtin(t_data *info, int i)
{
	if (!ft_strcmp(info->av[i], "exit"))
		return (1);
	else if (!ft_strcmp(info->av[i], "cd"))
		return (1);
	else if (!ft_strcmp(info->av[i], "env"))
		return (1);
	else if (!ft_strcmp(info->av[i], "setenv"))
		return (1);
	else if (!ft_strcmp(info->av[i], "unsetenv"))
		return (1);
	else if (!ft_strcmp(info->av[i], "echo"))
		return (1);
	return (0);
}*/

static int	start_with_operand(char *str)
{
	int		i;

	i = 0;
	while (str[i] && !is_operand(&str[i]))
		i++;
	if (!str[i])
		return (0);
	return (1);
}

static void	print_all_lexem(t_list *lexem_list)
{
	t_list	*current;
	int		i;

	write(0, "\n", 1);
	current = lexem_list;
	while (current)
	{
		i = 0;
		while (((t_lexem*)(current->data))->cmd[i][0])
		{
			ft_printf("{bold}{cyan}%s{res}\n", ((t_lexem*)(current->data))->cmd[i]);
			i++;
		}
		ft_printf("{bold}{green}OPREAND : %d{res}\n", ((t_lexem*)(current->data))->op);
		current = current->next;
		if (current)
			i = (((t_lexem*)(current->data))->cmd[i][0]) ? i + 1 : i;
	}
}

int			lexer(t_data *info)
{
	t_lexem	*lexem;
	int		i;
	int		j;

	i = 0;
	if (start_with_operand(info->av[0]))
		return (print_error(11));
	while (info->av[i][0])
	{
		j = 0;
		if (!(lexem = (t_lexem*)malloc(sizeof(t_lexem))))
			print_error(ERR_MALLOC);
		while (info->av[i][0])
		{
			ft_strcpy(lexem->cmd[j], info->av[i]);
			if (is_operand(info->av[i]))
				break;
			ft_inc(1, 2, &i, &j);
		}
		lexem->op = set_operand(info->av[i]);
		i = (info->av[i][0]) ? i + 1 : i;
		ft_push_back(&info->lexem_list, lexem);
	}
	print_all_lexem(info->lexem_list);
	return (1);
}

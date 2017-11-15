/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 22:16:31 by proso             #+#    #+#             */
/*   Updated: 2017/11/14 00:09:37 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static int	choice_direction(void *info, void *lex)
{
	(void)info;
	if (((t_lexem*)(lex))->op == PIPE)
		return (0);
	return (-1);
}

int			is_builtin(t_lexem *lex)
{
	if (!ft_strcmp(lex->cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(lex->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(lex->cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(lex->cmd[0], "setenv"))
		return (1);
	else if (!ft_strcmp(lex->cmd[0], "unsetenv"))
		return (1);
	else if (!ft_strcmp(lex->cmd[0], "echo"))
		return (1);
	return (0);
}

int			start_with_operand(char *str)
{
	int		i;

	i = 0;
	while (str[i] && !is_operand(&str[i]))
		i++;
	if (!str[i])
		return (0);
	return (1);
}

static void	bt_iter(t_data *info, t_btree *root, int (f)(t_data *, t_lexem *))
{
	t_btree	*current;
	int		op;
	int		ret;
	int		pass;

	ft_init(0, 2, &pass, &ret);
	current = root;
	if (current)
	{
		op = ((t_lexem*)(current->item))->op;
		if (op == SEMICOLON || op == AND)
			ret = f(info, current->item);
		else
			pass = 0;
		if (current->left)
			bt_iter(info, current->left, f);
		if (current->right)
			bt_iter(info, current->right, f);
		if (pass != 2 && pass != -2)
			ret = f(info, current->item);
	}
}

void		parser(t_data *info)
{
	t_list	*current;

	current = info->lexem_list;
	if (!current)
		return ;
	while (current)
	{
		btree_insert_data(&info->root, current->data, choice_direction);
		current = current->next;
	}
	bt_iter(info, info->root, exectute);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 14:40:35 by proso             #+#    #+#             */
/*   Updated: 2017/12/01 01:28:59 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

static void	pass_space(char *buf, int *i, int *sg_qu, int *db_qu)
{
	while (buf[*i])
	{
		if ((buf[*i] == ' ' || buf[*i] == '\n') && !*sg_qu && !*db_qu)
			(*i)++;
		else if ((buf[*i] == ' ' || buf[*i] == '\n') && (*sg_qu || *db_qu))
			return ;
		else if (buf[*i] != ' ' && buf[*i] != '\n')
			return ;
		if (buf[*i] == '\'' && !*db_qu)
			*sg_qu = (!*sg_qu) ? 1 : 0;
		else if (buf[*i] == '\"' && !*sg_qu)
			*db_qu = (!*db_qu) ? 1 : 0;
	}
}

static void	pass_no_space(char *buf, int *i, int *sg_qu, int *db_qu)
{
	while (buf[*i])
	{
		if ((buf[*i] == ' ' || buf[*i] == '\n') && !*sg_qu && !*db_qu)
			return ;
		if (is_operand(buf[*i]) && !*sg_qu && !*db_qu)
			return ;
		else if ((buf[*i] == ' ' || buf[*i] == '\n') && (*sg_qu || *db_qu))
			(*i)++;
		else if (buf[*i] != ' ' && buf[*i] != '\n')
			(*i)++;
		if (buf[*i] == '\'' && !*db_qu)
			*sg_qu = (!*sg_qu) ? 1 : 0;
		else if (buf[*i] == '\"' && !*sg_qu)
			*db_qu = (!*db_qu) ? 1 : 0;
	}
}

static void	create_new_lexem(t_data *info, int *i, t_list *list)
{
	t_lexem	*lexem;

	if (!(lexem = (t_lexem*)malloc(sizeof(t_lexem))))
		print_error(ERR_MALLOC);
	lexem->cmd = ft_list_to_tab(list);
	lexem->op = get_operand(info->buf_cmd, *i);
	ft_push_back(&info->lexem_list, lexem);
	if (lexem->op == OR || lexem->op == AND || lexem->op == REDIR_LL ||
														lexem->op == REDIR_RR)
		*i = *i + 2;
	else if (lexem->op != BK)
		(*i)++;
}

/*static void	print_all_lexem(t_list *lexem_list)
{
	t_list	*current;
	int		i;

	write(0, "\n", 1);
	current = lexem_list;
	while (current)
	{
		i = 0;
		if (!((t_lexem*)(current->data))->cmd[i] || !((t_lexem*)(current->data))->cmd[i][0])
			ft_printf("{bold}{red}($NULL){res}\n");
		while (((t_lexem*)(current->data))->cmd[i] && ((t_lexem*)(current->data))->cmd[i][0])
		{
			ft_printf("{bold}{cyan}%s{res}\n", ((t_lexem*)(current->data))->cmd[i]);
			i++;
		}
		ft_printf("{bold}{green}OPREAND : %d{res}\n", ((t_lexem*)(current->data))->op);
		if (current->next)
			i++;
		current = current->next;
	}
}*/

static int	suite_lexer(t_data *info, int *i, int j, t_list **tmp_list)
{
	if (info->buf_cmd[j] != ' ' && info->buf_cmd[j] != '\n')
	{
		create_new_lexem(info, i, *tmp_list);
		ft_remove_list(tmp_list);
	}
	add_cmd_to_history(info);
	clean_lexem(info);
	//print_all_lexem(info->lexem_list);
	parser(info);
	return (1);
}

int			lexer(t_data *info)
{
	t_list	*tmp_list;
	int		i;
	int		j;
	int		sg_quote;
	int		db_quote;

	i = 0;
	tmp_list = NULL;
	sg_quote = (info->buf_cmd[i] == '\'') ? 1 : 0;
	db_quote = (info->buf_cmd[i] == '\"') ? 1 : 0;
	while (info->buf_cmd[i])
	{
		pass_space(info->buf_cmd, &i, &sg_quote, &db_quote);
		j = i;
		if (!info->buf_cmd[i])
			break ;
		pass_no_space(info->buf_cmd, &i, &sg_quote, &db_quote);
		if (i - j)
			ft_push_back(&tmp_list, ft_strsub(info->buf_cmd, j, i - j));
		if (is_operand(info->buf_cmd[i]))
		{
			create_new_lexem(info, &i, tmp_list);
			ft_remove_list(&tmp_list);
		}
	}
	return (suite_lexer(info, &i, j, &tmp_list));
}

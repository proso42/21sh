/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:04:11 by proso             #+#    #+#             */
/*   Updated: 2017/11/25 04:32:22 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/shell.h"

int	builtin_echo(char **arg)
{
	int		i;
	int		j;
	int		sg_quote;
	int		db_quote;

	i = 1;
	j = 0;
	while (arg[i] && arg[i][0])
	{
		if (arg[i][j] == '\'')
			sg_quote = (!sg_quote && !db_quote) ? 1 : 0;
		else if (arg[i][j] == '\"')
			db_quote = (!db_quote && !sg_quote) ? 1 : 0;
		if ((arg[i][j] == '\'' && db_quote) || (arg[i][j] == '\"' && sg_quote)
								|| ((arg[i][j] != '\'') && arg[i][j] != '\"'))
			write(0, &arg[i][j], 1);
		if (arg[i][j + 1])
			j++;
		else if (arg[i + 1][0])
		{
			j = 0;
			i++;
		}
		else
			break ;
	}
	write(0, "\n", 1);
	return (1);
}

int	builtin_exit(char **arg)
{
	int		ret;
	int		i;

	i = 0;
	if (arg[0] && arg[1] && arg[2] && arg[2][0])
	{
		print_error(9);
		return (0);
	}
	else if (!(arg[1]))
		exit(0);
	else
		ret = ft_atoi(arg[1]);
	while (arg[1][i])
	{
		if (!ft_isdigit(arg[1][i]))
		{
			print_error(10);
			exit(255);
		}
		i++;
	}
	exit(ret);
	return (1);
}

int	builtin_env(t_data *info, char **arg)
{
	t_list	*current;

	if (arg[1])
	{
		print_error(9);
		return (0);
	}
	current = info->env_list;
	while (current)
	{
		ft_putendl(((t_env*)(current->data))->env_complete);
		current = current->next;
	}
	return (1);
}

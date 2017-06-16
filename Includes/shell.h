/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 11:35:13 by proso             #+#    #+#             */
/*   Updated: 2017/05/31 11:35:17 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/signal.h>
# include "libft.h"

# define ERR_TERM	4
# define ERR_MALLOC 6

typedef struct	s_env
{
	char		*env_name;
	char		*env_value;
	char		*env_complete;
}				t_env;

typedef struct	s_data
{
	t_list			*env_list;
	char			*cmd_line;
	struct termios	sh_term;
	struct termios	df_term;
	struct winsize	sz;
	char			buf_cmd[1024];
	int				buf_i;
	int				curs_x;
	int				curs_y;
	int				prompt_size;
}					t_data;

int				init_terminal(t_data *info);
int				default_terminal(t_data *info, int mode);
int				error(int err);
t_list			*init_env_list(void);
int				get_stdin(t_data *info);
void			term_action(char *action);
int				add_to_buf(t_data *info, char *key);
int				edit_buf(t_data *info, char *key);
int				line_edition(t_data *info, char *key);

#endif

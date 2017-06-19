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

typedef struct	s_cmd
{
	int			type;
	char		name[100];
}				t_cmd;

typedef struct	s_data
{
	t_list			*env_list;
	t_list			*history_list;
	char			tmp_buf[1024];
	int				num_history;
	struct termios	sh_term;
	struct termios	df_term;
	struct winsize	sz;
	char			buf_cmd[1024];
	char			av[100][100];
	int				buf_i;
	int				curs_x;
	int				curs_y;
	int				prompt_size;
	int				quote;
	int				j;
}					t_data;

int				init_terminal(t_data *info);
int				default_terminal(t_data *info, int mode);
int				print_error(int err);
void			print_prompt(t_data *info);
t_list			*init_env_list(void);
void			builtin_env(t_data *info);
int				get_stdin(t_data *info);
void			term_action(t_data *info, char *action);
int				add_to_buf(t_data *info, char *key);
int				edit_buf(t_data *info, char *key);
int				line_edition(t_data *info, char *key);
void			home(t_data *info, int mode);
void			end(t_data *info);
void			go_good_place(t_data *info);
void			move_next_word(t_data *info);
void			move_prev_word(t_data *info);
void			move_left(t_data *info);
void			move_right(t_data *info);
int				cut_cmd(t_data *info);
char			*get_env_var(t_data *info, char *str);
void			replace_dollard(t_data *info, char str[]);
void			write_buf(t_data *info);
void			del_line(t_data *info);
void			delete_left(t_data *info);
void			delete_right(t_data *info);
int				get_history(t_data *info, char *key);
void			add_cmd_to_history(t_data *info);
void			clear_sc(t_data *info);
void			eval_quote(t_data *info, int j);

#endif

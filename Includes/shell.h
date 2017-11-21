/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 11:35:13 by proso             #+#    #+#             */
/*   Updated: 2017/11/22 00:24:34 by proso            ###   ########.fr       */
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

# define ERR_TERM		4
# define ERR_MALLOC 	6
# define ERR_INEXISTANT	50
# define PERMISSION		51
# define ERR_DIRECTORY	52
# define EMPTY_HIST		53
# define AND 			100
# define OR 			101
# define SEMICOLON		102
# define REDIR_L 		103
# define REDIR_LL		104
# define REDIR_R		105
# define REDIR_RR		106
# define PIPE			107
# define AGREG			108
# define BK				109

typedef struct	s_lexem
{
	int			op;
	char		**cmd;
}				t_lexem;

typedef struct	s_env
{
	char		*env_name;
	char		*env_value;
	char		*env_complete;
}				t_env;

typedef struct	s_hist
{
	char		search[1024];
	char		key[6];
	int			nb_line;
	int			pos_list;
	t_list		*match_list;
}				t_hist;

typedef struct	s_data
{
	pid_t			pid;
	int				searching;
	t_list			*env_list;
	t_list			*history_list;
	t_list			*lexem_list;
	t_btree			*root;
	char			tmp_buf[1024];
	int				num_history;
	struct termios	sh_term;
	struct termios	df_term;
	struct winsize	sz;
	t_hist			*hist;
	char			buf_cmd[1024];
	char			av[1024][1024];
	char			*cpy;
	int				buf_i;
	int				curs_x;
	int				curs_y;
	int				prompt_size;
	int				quote;
}				t_data;

void			add_cmd_to_history(t_data *info);
int				add_to_buf(t_data *info, char *key);
int				builtin_cd(t_data *info, char *path);
int				builtin_echo(char ** arg);
int				builtin_env(t_data *info, char** arg);
int				builtin_exit(char ** arg);
int				builtin_setenv(t_data *info, char ** arg);
int				builtin_unsetenv(t_data *info, char ** arg);
char			*check_local_path(char *path);
int				check_path_error(char *path, int allow_print, int type);
void			create_min_env_var(t_data *info);
int				check_var(t_list *env_list, char *env);
void			clear_history_lines(t_data *info);
void			clear_sc(t_data *info);
int				cpy_mode(t_data *info);
int				history_search(t_data *info);
int				cut_cmd(t_data *info);
int				cut_mode(t_data *info);
int				default_terminal(t_data *info, int mode);
void			del(void *lex);
void			delete_left(t_data *info);
void			delete_right(t_data *info);
void			del_line(t_data *info);
int				edit_buf(t_data *info, char *key);
void			end(t_data *info);
void			event_cursor_history(t_data *info);
void			event_delete_history(t_data *info);
int				event_enter_history(t_data *info);
void			event_letter_history(t_data *info);
void			event_tab_history(t_data *info);
void			eval_quote(t_data *info, int j);
int				exec_builtin(t_data *info, t_lexem *lex);
int				exec_single(t_data *info, t_lexem *lex);
int				exectute(t_data *info, t_lexem *lex);
char			*find_cmd(t_data *info, char *path);
char			*get_env_var(t_data *info, char *str);
int				get_history(t_data *info, char *key);
void			get_match_data(t_data *info, char *search);
int				get_stdin(t_data *info);
void			go_good_place(t_data *info);
void			home(t_data *info, int mode);
t_list			*init_env_list(void);
int				init_line_edition(t_data *info);
void			init_signal(t_data *info);
int				init_terminal(t_data *info);
int				is_builtin(t_lexem *lex);
int				is_directory(char *path);
int				is_operand(char *c);
int				lexer(t_data *info);
void			lexer_parser(t_data *info);
int				line_edition(t_data *info, char *key);
void			move_down(t_data *info);
void			move_left(t_data *info);
void			move_next_word(t_data *info);
void			move_prev_word(t_data *info);
void			move_right(t_data *info);
void			move_up(t_data *info);
void			parser(t_data *info);
int				past_mode(t_data *info);
void			print_correct_history(t_data *info);
int				print_error(int err);
void			print_prompt(t_data *info);
void			replace_dollard(t_data *info, char str[]);
int				start_with_operand(char *str);
void			term_action(t_data *info, char *action);
void			term_tgoto(t_data *info, int x, int y);
void			write_buf(t_data *info);

#endif

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: proso <proso@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/27 13:41:20 by proso             #+#    #+#              #
#    Updated: 2017/11/05 00:51:16 by proso            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC = add_lexem.c \
	  add_to_buf.c \
	  builtin_cd.c \
	  builtin_setenv.c \
	  builtin_unsetenv.c \
	  check_path_error.c \
	  clear_sc.c \
	  cpy_mode.c\
	  cut_cmd.c \
	  cut_mode.c \
	  delete.c \
	  easy_builtin.c \
	  env.c \
	  eval_quote.c \
	  exec_single.c \
	  get_history.c \
	  get_stdin.c \
	  lexer.c \
	  line_edition.c \
	  main.c\
	  past_mode.c \
	  print_error.c \
	  replace_dollard.c \
	  signal.c \
	  spc_move_curs.c \
	  spc_move_curs2.c \
	  switch_terminal.c \
	  term_action.c \
	  tmp_action.c

CC = gcc

FLAGS = -Wall -Werror -Wextra

INCLUDE = Includes/shell.h

LIB = Libft/libft.a

OBJ = $(addprefix $(DIR_OBJ), $(SRC:.c=.o))

DIR_OBJ = ./OBJ/

DIR_SRC = ./Sources/

all: $(NAME)

$(DIR_OBJ)%.o	:	$(DIR_SRC)%.c $(INCLUDE)
	@$(CC) $(FLAGS) -I./$(INCLUDE) -o $@ -c $<
	@Progress_bar/p_bar_21sh $<
	@sleep 0.05

clr:
	@clear

make_lib:
	@make -C Libft/
	@clear
	@echo "\x1b[33m\x1b[1mMaking executable... ⏳\x1b[0m"
	@sleep 1

$(NAME): clr make_lib $(OBJ) $(INCLUDE)
	@$(CC) $(FLAGS) -o $(NAME) $(LIB) $(OBJ) -ltermcap
	@sleep 1
	@clear
	@echo "\x1b[32m\x1b[1mExecutable sucessfully created ✓\x1b[0m"

clean:
	@make clean -C Libft/
	@rm -f $(OBJ)
	@echo "\x1b[31m\x1b[1mAll objects deleted ✖\x1b[0m"

fclean: clean
	@make fclean -C Libft/
	@rm -f $(NAME)
	@echo "\x1b[31m\x1b[1mExecutable deleted ✖\x1b[0m"

re: fclean all

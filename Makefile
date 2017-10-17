# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: proso <proso@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/27 13:41:20 by proso             #+#    #+#              #
#    Updated: 2017/10/18 00:07:55 by proso            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21_sh

SRC = Sources/add_lexem.c \
	  Sources/add_to_buf.c \
	  Sources/builtin_cd.c \
	  Sources/builtin_setenv.c \
	  Sources/builtin_unsetenv.c \
	  Sources/check_path_error.c \
	  Sources/clear_sc.c \
	  Sources/cpy_mode.c\
	  Sources/cut_cmd.c \
	  Sources/cut_mode.c \
	  Sources/delete.c \
	  Sources/easy_builtin.c \
	  Sources/env.c \
	  Sources/eval_quote.c \
	  Sources/exec_single.c \
	  Sources/get_history.c \
	  Sources/get_stdin.c \
	  Sources/lexer.c \
	  Sources/line_edition.c \
	  Sources/main.c\
	  Sources/past_mode.c \
	  Sources/print_error.c \
	  Sources/replace_dollard.c \
	  Sources/signal.c \
	  Sources/spc_move_curs.c \
	  Sources/spc_move_curs2.c \
	  Sources/switch_terminal.c \
	  Sources/term_action.c \
	  Sources/tmp_action.c

CC = gcc

FLAGS = -Wall -Werror -Wextra

INCLUDE = Includes/shell.h

LIB = Libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c $(INCLUDE)
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

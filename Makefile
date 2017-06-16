# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: proso <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/27 13:41:20 by proso             #+#    #+#              #
#    Updated: 2017/06/09 15:27:35 by proso            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21_sh

SRC = Sources/main.c \
      Sources/terminal.c \
	  Sources/error.c \
	  Sources/term_action.c


	#Sources/add_to_buf.c \
	  Sources/edit_buf.c \
      Sources/env.c \
       \
	  Sources/get_stdin.c \
	  Sources/line_edition.c \#

	  # \
	  #

CC = gcc

FLAGS = -Wall -Werror -Wextra

INCLUDE = Includes/ft_select.h

LIB = Libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c
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

$(NAME): clr make_lib $(OBJ)
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

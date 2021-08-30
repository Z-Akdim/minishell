# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/30 09:56:40 by zakdim            #+#    #+#              #
#    Updated: 2021/08/30 09:56:42 by zakdim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB = minishell.a
CFLAGS = -Wall -Wextra -Werror

INC =-I./inc
EXEC = 		srcs/exec/ft_cd.c \
			srcs/exec/ft_echo.c \
			srcs/exec/ft_export.c \
			srcs/exec/ft_init.c \
			srcs/exec/ft_pwd.c \
			srcs/exec/ft_redirection.c \
			srcs/exec/ft_unset.c \
			srcs/exec/main.c \
			srcs/exec/ft_command_run.c \
			srcs/exec/ft_dup2.c \
			srcs/exec/ft_env.c \
			srcs/exec/ft_start.c \
			srcs/exec/ft_free_all.c \
			srcs/exec/ft_pipe_1.c \
			srcs/exec/ft_shell_lvl.c \
			srcs/exec/ft_pipe_2.c \
			srcs/exec/ft_export_1.c \
			srcs/exec/ft_free_all_1.c \
			srcs/exec/ft_redirection_1.c \
			srcs/exec/ft_get_line.c \
			srcs/exec/ft_get_line_utils.c \
			srcs/exec/ft_start_2.c

PARSSING =	srcs/parssing/ft_get_args.c \
			srcs/parssing/ft_get_path.c \
			srcs/parssing/ft_multi_command.c \
			srcs/parssing/syn_error.c \
			srcs/parssing/ft_split.c \
			srcs/parssing/ft_dollar.c \
			srcs/parssing/ft_copy.c \
			srcs/parssing/ft_sort_args_1.c \
			srcs/parssing/ft_sort_args_2.c \
			srcs/parssing/ft_quotes.c \
			srcs/parssing/minishell_utils.c \
			srcs/parssing/ft_signal.c \
			srcs/parssing/get_next_line.c \
			srcs/parssing/get_next_line_utils.c \
			srcs/parssing/ft_pipe.c \
			srcs/parssing/ft_redirection_syn.c  \
			srcs/parssing/ft_redirection_syn_1.c  \
			srcs/parssing/minishell_utils_2.c \
			srcs/parssing/minishell_utils_3.c \
			srcs/parssing/ft_dollar_2.c \
			srcs/parssing/ft_dollar_3.c



SRCS=		$(PARSSING) \
			$(EXEC)

OBJ=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(LIB) $(OBJ)
	@gcc $(CFLAGS) $(INC)  -o $(NAME) $(OBJ) $(LIB)
	@echo "\033[1;33mMake \033[1;32m\t    [OK]"
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "\033[1;32m| \033[1;33m" $(NAME) : Created ! "\033[1;32m|"
	@echo "\033[1;32m~~~~~~~~~~~~~~~~~~~~~~~~~~"

%.o: %.c
	@gcc $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@echo "\033[1;33mMake clean \033[1;32m [OK]"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB)
	@echo "\033[1;33mMake fclean \033[1;32m[OK]"

re:
	@make fclean
	@make all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/26 15:28:45 by lyie              #+#    #+#              #
#    Updated: 2021/10/19 16:37:25 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/minishell_main/minishell_main.c \
		srcs/minishell_main/minishell_main_2.c \
		srcs/minishell_main/execute.c \
		srcs/minishell_main/execute_2.c \
		srcs/minishell_main/execute_3.c \
		srcs/minishell_main/execute_4.c \
		srcs/minishell_main/hello_doc_bonus.c \
		srcs/minishell_main/my_comands.c \
		srcs/minishell_main/my_commands_2.c \
		srcs/minishell_main/directing_stuff.c \
		srcs/minishell_main/directing_stuff_tools.c \
		srcs/minishell_main/signals.c \
		srcs/builtins/env.c \
		srcs/builtins/export.c \
		srcs/builtins/export_tools.c \
		srcs/builtins/export_tools_ter.c \
		srcs/builtins/free_envp.c \
		srcs/builtins/unset.c \
		srcs/builtins/dollar_qmark_case.c \
		srcs/builtins/dollar_qmark_case_2.c \
		srcs/parsing/parse_unclosed.c \
		srcs/parsing/ft_split_quotes.c \
		srcs/parsing/ft_split_quotes_2.c \
		srcs/parsing/ft_dequote.c \
		srcs/parsing/ft_dequote_2.c \
		srcs/parsing/ft_punctuation.c \
		srcs/parsing/ft_punctuation_2.c \
		srcs/parsing/ft_punctuation_3.c \
		srcs/parsing/ft_dequote_orig.c \
		srcs/parsing/ft_dequote_export.c \
		srcs/parsing/ft_dequote_list.c \
		srcs/parsing/directions.c \
		srcs/parsing/ft_atoi_mod.c \
		srcs/parsing/ft_hang_pipe.c \
		srcs/parsing/directions_2.c \
		srcs/parsing/directions_3.c \
		srcs/parsing/directions_4.c \
		srcs/parsing/directions_tools.c \
		srcs/parsing/functions_bonus.c \
		srcs/tools/get_next_line_utils.c \
		srcs/tools/get_next_line.c \
		srcs/tools/get_next_line_2.c \
		srcs/tools/list_tools_extra.c \
		srcs/tools/list_tools_more.c \
		srcs/tools/str_functions_bonus.c \
		srcs/tools/tools_2_bonus.c \
		srcs/tools/tools_3_bonus.c \
		srcs/tools/big_free.c \
		srcs/tools/tools_4.c \
		srcs/tools/tools_bonus.c \
		srcs/builtins/export_tools_bis.c \
		srcs/builtins/dequote_tools.c \
		srcs/minishell_main/convert_env_in_tab.c \
		srcs/parsing/variables.c \
		srcs/parsing/variables_2.c \
		srcs/parsing/variable_dolars.c \
		srcs/parsing/variables_tools.c 
		
OBJS = ${SRCS:.c=.o}
INCLUDES = -I./include
NAME = minishell
CC = clang
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3


all: ${NAME}

$(NAME)	: ${OBJS}
	make -s -C ./libft
	${CC} ${CFLAGS} -I${INCLUDES} ${OBJS} -lreadline -Llibft -lft -o $(NAME)
clean:
	make -s clean -C ./libft
	${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	make -s fclean -C ./libft
	${RM} ${NAME} ${NAME_BONUS}

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 19:20:08 by mlecuyer          #+#    #+#              #
#    Updated: 2021/09/07 17:32:39 by mlecuyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror

SRCS =	ft_atoi.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strdup.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_calloc.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_split.c \
		ft_strcmp.c \
		ft_strchr_int.c  \
		ft_strchr_original.c 
		

OBJS		=	${SRCS:.c=.o}

NAME		=	libft.a

RM			=	rm -f

.c.o:	
			${CC} ${CFLAGS} -I. -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
				ar -rc ${NAME} ${OBJS}

clean:		
			${RM} ${OBJS} ${OBJS_BONUS}
fclean:		clean
				${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
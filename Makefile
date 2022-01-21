# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 07:41:25 by apommier          #+#    #+#              #
#    Updated: 2022/01/21 07:43:46 by apommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
SRCS	= main.c \
			utils.c
OBJS	= ${SRCS:.c=.o}
BONUS_C	= main.c \
			utils.c
BONUS_O	= ${BONUS_C:.c=.o}
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
LIBFT	= ./libft


${NAME}:${OBJS} 
		make bonus -C ${LIBFT}
		gcc -g ${OBJS} ${LIBFT}/libft.a
		mv a.out pipex

bonus:${BONUS_O}
		make bonus -C ${LIBFT}
		gcc -g ${CFLAGS} ${BONUS_O} ${LIBFT}/libft.a 
		mv a.out pipex

all:	${NAME} bonus

clean:
		${RM} ${OBJS}
		${RM} ${BONUS_O}
		make clean -C ${LIBFT}

fclean:	clean
		${RM} ${NAME}
		make fclean -C ${LIBFT}
		
re: 	fclean all

.PHONY: all clean fclean re bonus 

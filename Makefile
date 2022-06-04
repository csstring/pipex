# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 17:04:36 by schoe             #+#    #+#              #
#    Updated: 2022/06/04 14:27:41 by schoe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
SRCS = main.c pipex.c
OBJS = ${SRCS:.c=.o}
RM = rm -f
INCLUDE = -I./includes
NAME = pipex

all : $(NAME)

$(NAME) : ${OBJS}
		${MAKE} -C ./libft all
		${CC} ${CFLAGS} ${OBJS} libft.a -o pipex

%.o : %.c
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INCLUDE}

clean :
		${MAKE} -C ./libft clean
		${RM} ${OBJS}

fclean : clean
		${MAKE} -C ./libft fclean
		${RM} $(NAME)
re : 
	${MAKE} fclean 
	${MAKE} all

.PHONY: all clean fclean re

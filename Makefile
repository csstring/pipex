# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 17:04:36 by schoe             #+#    #+#              #
#    Updated: 2022/06/20 13:10:05 by schoe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
BSRCS = ./b_src/main_bonus.c ./b_src/ft_cmd_bonus.c \
		./b_src/ft_pipe_utils_bonus.c ./b_src/ft_error_check_bonus.c \
		./b_src/ft_parsing_bonus.c
SRCS = ./m_src/main.c ./m_src/ft_parsing.c ./m_src/ft_cmd.c \
	   ./m_src/ft_error_check.c ./m_src/ft_pipe_utils.c
OBJS = ${SRCS:.c=.o}
BOBJS = ${BSRCS:.c=.o}
RM = rm -f
INCLUDE = -I./includes
NAME = pipex

ifdef BONUS
	OBJ = ${BOBJS}
else
	OBJ = ${OBJS}
endif

all : $(NAME)

$(NAME) : ${OBJ}
		${MAKE} -C ./libft all
		${CC} ${CFLAGS} ${OBJ} libft.a -o pipex

%.o : %.c
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INCLUDE}

bonus :
	make BONUS=1

clean :
		${MAKE} -C ./libft clean
		${RM} ${BOBJS}
		${RM} ${OBJ}

fclean : clean
		${MAKE} -C ./libft fclean
		${RM} $(NAME)
re : 
	${MAKE} fclean 
	${MAKE} all

.PHONY: all clean fclean re bonus

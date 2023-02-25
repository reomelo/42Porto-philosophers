# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riolivei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 10:49:40 by riolivei          #+#    #+#              #
#    Updated: 2023/02/23 18:43:21 by riolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRCS = src/main.c src/utils.c src/utils2.c src/actions.c
OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.SILENT:

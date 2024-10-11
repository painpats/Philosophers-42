# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbourre <cbourre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 13:31:13 by cbourre           #+#    #+#              #
#    Updated: 2023/04/01 18:02:07 by cbourre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### FILES ################################################################

NAME = philo

SRC = 	philo.c \
		check_args.c \
		get_data.c \
		game.c \
		actions.c \
		get_time.c \
		utils.c 

SRCS = $(addprefix sources/, $(SRC))

OBJS = $(SRCS:.c=.o)

#### COMPIL ###############################################################

CC =		clang

CFLAGS =	-Wall -Wextra -Werror -I. -pthread

RM =		rm -rf

#### RULES ################################################################

all: $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

#### BIN ##################################################################

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

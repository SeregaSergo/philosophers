# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bswag <bswag@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/20 17:19:13 by bswag             #+#    #+#              #
#    Updated: 2021/05/11 23:14:42 by bswag            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo_three
SRCS =		main.c \
			utils.c \
			process.c \
			main_proc.c
PATHSRC =	./srcs/
OBJS =		$(SRCS:%.c=%.o)
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
PATHINC =	./includes/
DEPS =		$(PATHINC)philo_three.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(addprefix $(PATHSRC),$(OBJS))
	$(CC) $(CFLAGS) -I$(DEPS) $(addprefix $(PATHSRC),$(OBJS)) -o $(NAME)

%.o: $(PATHSRC)%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	/bin/rm -f $(addprefix $(PATHSRC), $(OBJS))

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

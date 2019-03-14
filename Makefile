# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 23:46:05 by jaleman           #+#    #+#              #
#    Updated: 2019/03/14 11:27:15 by rymuller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libftprintf.a

CFLAGS	= -c -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(patsubst %.c,%.o,$(wildcard *.c))
	ar rs $(NAME) $?

%.o: %.c
	gcc $(CFLAGS) -I includes/ $<

clean:
	/bin/rm -rf *.o

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

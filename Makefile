# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 18:55:02 by iksaiz-m          #+#    #+#              #
#    Updated: 2025/01/20 20:09:50 by iksaiz-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR    = libft/
CFLAGS       = -Wall -Wextra -Werror -g -O3 -g3

NAME         = philo
RM           = rm -rf
SRC = dinner.c arguments.c

OBJS = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
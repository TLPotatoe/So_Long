# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/15 15:55:14 by tlamit            #+#    #+#              #
#    Updated: 2026/01/15 16:01:44 by tlamit           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc

SRCS_DIR := src

SRCS := so_long.c

HEADER := -I includes \
		-I Libft_C

NAME := client
OBJS := $(SRCS_CLIENT:.c=.o)

LIBFT 		:= Libft_C/libft.a
MINILIBX	:= minilibx-linux/libmlx.a

LIBS := $(LIBFT)

ifndef DEBUG
	CFLAGS := -Wall -Wextra -Werror -g $(HEADER)
else
	CFLAGS := -g $(HEADER)
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C Libft_C -j

$(MINILIBX):
	$(MAKE) -C minilibx -j

clean:
	rm -f $(OBJS)
	$(MAKE) -C Libft_C clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C Libft_C fclean

re: fclean all

.PHONY: all clean fclean re
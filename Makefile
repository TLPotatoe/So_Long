# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/15 15:55:14 by tlamit            #+#    #+#              #
#    Updated: 2026/01/16 19:09:39 by tlamit           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc

SRCS := so_long.c

HEADER := -I includes \
		-I Libft_C

NAME := so_long
OBJS := $(SRCS:.c=.o)

LIBFT_DIR	:=	Libft_C
LIBFT 		:=	$(LIBFT_DIR)/libft.a

MacroLibX_DIR	:= MacroLibX
MacroLibX		:= $(MacroLibX_DIR)/libmlx.so

LIBS := $(LIBFT) $(MacroLibX)
SDL_LIBS := -lSDL2 -lvulkan -ldl -lm -pthread

ifndef DEBUG
	CFLAGS := -Wall -Wextra -Werror -g $(HEADER)
else
	CFLAGS := -g $(HEADER)
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) $(SDL_LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


$(LIBFT): submodule_init
	$(MAKE) -C $(LIBFT_DIR) -j

$(MacroLibX): submodule_init
	$(MAKE) -C $(MacroLibX_DIR) -j

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MacroLibX_DIR) clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MacroLibX_DIR) fclean

re: fclean all

submodule_init:
	git submodule update --init --recursive

.PHONY: all clean fclean re submodule_init
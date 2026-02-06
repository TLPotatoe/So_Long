# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlamit <titouan.lamit@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/15 15:55:14 by tlamit            #+#    #+#              #
#    Updated: 2026/02/06 19:56:15 by tlamit           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc

SRCS_DIR := src/
SRCS_PARSE_DIR := $(SRCS_DIR)/parse/
SRCS_GAME_DIR := $(SRCS_DIR)/game/
SRCS_UTILS_DIR := $(SRCS_DIR)/utils/

SRCS_PARSE := $(SRCS_PARSE_DIR)/parser.c \
			$(SRCS_PARSE_DIR)/check_map.c  \
			$(SRCS_PARSE_DIR)/flood_fill.c

SRCS_GAME := $(SRCS_GAME_DIR)/game.c \
			$(SRCS_GAME_DIR)/moves.c

SRCS_UTILS := $(SRCS_UTILS_DIR)/utils.c \
			$(SRCS_UTILS_DIR)/game_utils.c \
			$(SRCS_UTILS_DIR)/images_utils.c

SRCS := so_long.c \
		$(SRCS_PARSE) \
		$(SRCS_GAME) \
		$(SRCS_UTILS)

HEADER := -I includes \
		-I libft \
		-I MacroLibX/includes

NAME := so_long
OBJS := $(SRCS:.c=.o)

LIBFT_DIR	:=	libft
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


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) -j

$(MacroLibX):
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
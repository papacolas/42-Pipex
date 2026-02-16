# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 15:05:06 by ncrivell          #+#    #+#              #
#    Updated: 2025/03/15 16:41:31 by ncrivell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRCS = src/main.c src/utils.c src/paths.c \
		utils/split.c utils/strjoin.c

SRCS_BONUS = 	src_bonus/main_bonus.c \
				src_bonus/utils_bonus.c \
				src_bonus/heredoc_bonus.c \
				src_bonus/fork_bonus.c \
				src_bonus/paths_bonus.c \
				src_bonus/struct_bonus.c \
				utils/split.c \
				utils/strjoin.c \
				src/utils.c \
				utils_bonus/gnl_bonus.c \
				utils_bonus/gnl_utils_bonus.c \
				utils_bonus/clean_utils_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)


all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(BONUS_NAME): $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJS_BONUS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re

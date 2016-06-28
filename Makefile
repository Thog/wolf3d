# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/02 17:03:41 by tguillem          #+#    #+#              #
#    Updated: 2016/06/28 15:42:26 by tguillem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -g -Wall -Wextra -Werror -O3 -march=native -I./includes
PRGFLAGS = -lft -lmlx -framework OpenGL -framework AppKit
CC = gcc

NAME = wolf3d
LIB = libft
SRC = display.c graphics.c hooks.c image.c init.c io_utils.c main.c move.c utils.c
SRCDIR = src
OUTDIR = out
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(addprefix $(OUTDIR)/, $(SRC:.c=.o))

$(NAME): $(OUTDIR) $(OBJ)
	@$(MAKE) -C $(LIB)
	@$(CC) -o $(NAME) $(CFLAGS) -I./libft -L./libft $(PRGFLAGS) $(OBJ)
$(OUTDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -I $(LIB) -o $@ -c $? $(CFLAGS)

$(OUTDIR):
	@mkdir -p $(OUTDIR)

clean:
	@$(MAKE) -C $(LIB) $@
	@rm -f $(OBJ)
	@rm -rf $(OUTDIR)

fclean: clean
	@$(MAKE) -C $(LIB) $@
	@rm -f $(NAME)

.PHONY: clean fclean re

re: fclean all

all: $(NAME)

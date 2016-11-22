# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/02 17:03:41 by tguillem          #+#    #+#              #
#    Updated: 2016/07/18 17:19:34 by tguillem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -g -Wall -Wextra -Werror -I./includes
PRGFLAGS = -framework OpenGL -framework AppKit -L./libmlx -lmlx -L/tmp/ -L./libft -lft
CC = gcc

NAME = wolf3d
LIBFT = libft
LIBMLX = libmlx
SRC = display.c graphics.c hooks.c image.c init.c io_utils.c main.c move.c \
	  utils.c raycasting.c
SRCDIR = src
OUTDIR = out
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(addprefix $(OUTDIR)/, $(SRC:.c=.o))

$(NAME): $(OUTDIR) $(OBJ)
	make -C $(LIBFT)
	make -C $(LIBMLX)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(PRGFLAGS)

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I $(LIBFT) -I $(LIBMLX) -o $@ -c $? $(CFLAGS)

$(OUTDIR):
	@mkdir -p $(OUTDIR)

clean:
	make -C $(LIBFT) $@
	make -C $(LIBMLX) $@
	@rm -f $(OBJ)
	@rm -rf $(OUTDIR)

fclean: clean
	make -C $(LIBFT) $@
	@rm -f $(NAME)

.PHONY: clean fclean re

re: fclean all

all: $(NAME)

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 23:26:47 by ngomes-t          #+#    #+#              #
#    Updated: 2022/11/02 02:10:18 by ngomes-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

PATH_SRC = ./sources/
PATH_OBJ = ./objects/
PATH_INC = ./includes/
PATH_LIB = ./42_libft/

SRCS = $(addprefix $(PATH_SRC), fdf.c)

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRCS))

LIBFT = $(PATH_LIB)/libft.a

CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lm -lX11 -lXext -lmlx
IFLAGS = -I $(PATH_INC)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LFLAGS) $(LIBFT)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	mkdir -p $(PATH_OBJ)
	cc $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(PATH_LIB)

clean:
	make clean -C $(PATH_LIB)
	rm -rf $(PATH_OBJ)

fclean: clean
	make fclean -C $(PATH_LIB)
	rm -rf $(NAME)

re: fclean all

test: all
	./fdf ./test_maps/42.fdf
	
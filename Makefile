NAME = fdf

PATH_SRC = ./sources/
PATH_OBJ = ./objects/
PATH_INC = ./includes/
PATH_LIB = ./42_libft/
PATH_MLX = ./minilibx-linux/

SRCS = $(addprefix $(PATH_SRC), main.c)

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRCS))

LIBFT = $(PATH_LIB)/libft.a
MLX = $(PATH_MLX)/libmlx_Linux.a
MLX2 = $(PATH_MLX)/libmlx.a

CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lm -lX11 -lXext -lmlx -lmlx_Linux 
IFLAGS = -I $(PATH_INC) -I $(PATH_MLX) -I $(PATH_LIB)
PATH_LIBS = -L$(PATH_LIB) -L$(PATH_MLX)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX) $(MLX2)
	cc $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LFLAGS) $(PATH_LIBS) $(LIBFT) $(MLX) $(MLX2)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	mkdir -p $(PATH_OBJ)
	cc $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(PATH_LIB)

$(MLX):
	make -C $(PATH_MLX)

clean:
	make clean -C $(PATH_LIB)
	rm -rf $(PATH_OBJ)

fclean: clean
	make fclean -C $(PATH_LIB)
	rm -rf $(NAME)

re: fclean all

test: all
	./fdf ./test_maps/42.fdf
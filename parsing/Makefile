CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -Lminilibx-linux -lXext -lX11 -lm -lz

NAME = so_long

BONUS_NAME = so_long_bonus

LIBFT_DIR = ./libft
LIBFT = libft/libft.a

SRC = parsing.c parsing_map_creation.c \
		utils.c so_long.c \


OBJ = $(SRC:.c=.o)

MINILIBX_DIR = ./minilibx-linux

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(MINILIBX_DIR)/libmlx.a:
	@$(MAKE) -C $(MINILIBX_DIR) --quiet

$(NAME): $(OBJ) cleanup.o $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) cleanup.o $(LIBFT) -o $(NAME)

bonus: $(NAME)

#$(BONUS_NAME): $(OBJ) $(BONUS_OBJS) $(LIBFT) $(MINILIBX_DIR)/libmlx.a
		#$(CC) $(CFLAGS) $(BONUS_OBJS) $(OBJ)  $(LIBFT) $(MLXFLAGS) -o $(BONUS_NAME)#

%.o : %.c
	$(CC) $(CFLAGS) -I$(CURDIR) -I$(MINILIBX_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet
#	@$(MAKE) -C $(MINILIBX_DIR) clean --quiet

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

.PHONY: all clean fclean re

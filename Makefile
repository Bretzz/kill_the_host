# define standard colors
BOLD			= \033[1m
BLACK    		= \033[30m    # Black
RED      		= \033[31m    # Red
GREEN    		= \033[32m    # Green
YELLOW   		= \033[33m    # Yellow
BLUE     		= \033[34m    # Blue
MAGENTA  		= \033[35m    # Magenta
CYAN     		= \033[36m    # Cyan
WHITE    		= \033[37m    # White
LIGHT_RED		= \033[91m
LIGHT_GREEN		= \033[92m
LIGHT_CYAN		= \033[96m
RESET			= \033[0m

NAME			:= game
UNAME			:= $(shell uname)
CC				:= cc
CFLAGS			:= -Wall -Wextra #-Werror


#Libs
LIBFT_DIR		= libft/
LIBFT			= $(LIBFT_DIR)libft.a
HPC_DIR			= hpc/
HPC				= $(HPC_DIR)hpc.a

#Linkers
LINKS			= -L/usr/lib -L$(MLX_DIR) -lXext -lX11 -lm -lz -lpthread -L$(LIBFT_DIR)

#Includes
INKS			= -I$(CURDIR) -I$(LIBFT_DIR) -I$(HPC_DIR)include

ifeq ($(UNAME),Darwin)
	MLX_DIR		= minilibx_opengl
	MLX			= $(MLX_DIR)/libmlx.a
	URL			= https://cdn.intra.42.fr/document/document/34410/minilibx_macos_opengl.tgz
	DEFS		=
	INKS		+= -I/usr/X11/include -I$(MLX_DIR)-I/opt/homebrew/include -I/usr/X11/include
	LINKS		+= -L/usr/X11/lib -framework OpenGL -framework AppKit
else ifeq ($(UNAME),Linux)
	MLX_DIR		= minilibx-linux
	MLX			= $(MLX_DIR)/libmlx_$(UNAME).a
	URL			= https://cdn.intra.42.fr/document/document/34409/minilibx-linux.tgz
	DEFS		=
	INKS		+= -I/usr/include -I$(MLX_DIR)
	LINKS		+= -lmlx_Linux
else
	UNAME = Error
endif

#source files (expected in the root folder)
SRCS_DIR		=
SRC_FILES		= main.c \
				minigame.c \
				clean_exit.c \
				input_handling.c put_stuff.c \
				\
				parsing.c \
				parsing_map_creation.c \
				utils.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

VPATH 			= minigame/ parsing \
				utils/

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $< -o $@

test: main.c $(OBJS)
	@echo "${BOLD}compiling $@...${RESET}"
	@$(CC) $(CFLAGS) main.c $(OBJS_DIR)/* $(LINKS) $(INKS) -o $@ \
	&& echo "${LIGHT_GREEN}DONE${RESET}"

$(MLX_DIR):
	@echo "${BOLD}creating $(MLX_DIR)...${RESET}"
	@curl $(URL) --output $(MLX_DIR).tgz \
	&& tar -xf $(MLX_DIR).tgz \
	&& rm -f $(MLX_DIR).tgz \
	&& ls $(MLX_DIR) || mv `ls | grep $(MLX_DIR)` $(MLX_DIR) \
	&& $(MAKE) -C $(MLX_DIR)

$(MLX): $(MLX_DIR)
	@rm -f $(MLX_DIR)/libmlx.a
	@$(MAKE) -C $(MLX_DIR) --quiet

$(LIBFT):
	@echo "${BOLD}compiling libft...${RESET}"
	@$(MAKE) all -C $(LIBFT_DIR) --quiet

$(HPC):
	@echo "${BOLD}compiling hpc...${RESET}"
	@$(MAKE) all -C $(HPC_DIR) --quiet

$(NAME): $(LIBFT) $(HPC) $(MLX) $(OBJS)
	@echo "${BOLD}compiling the $(NAME)...${RESET}"
	$(CC) $(CFLAGS) $(OBJS) $(HPC) $(LIBFT) $(MLX) $(INKS) $(LINKS) -o $(NAME)
	@echo "${LIGHT_GREEN}DONE${RESET}"

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MLX_DIR)" ./*

clean:
	@rm -f $(OBJS_DIR)* game test
	@$(MAKE) clean -C $(LIBFT_DIR) --quiet
	@$(MAKE) clean -C $(HPC_DIR) --quiet

fclean: clean
	@rm -rf $(OBJS_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR) --quiet
	@$(MAKE) fclean -C $(HPC_DIR) --quiet

lre: clean all

re: fclean all
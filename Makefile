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
CFLAGS			:= -Wall -Wextra -Werror

#Libs
LIBFT			= libft/
MSG				= msg/
LBB				= lbb/

#Linkers
LINKS			= -L/usr/lib -L$(MLX_DIR) -lXext -lX11 -lm -lz -lpthread

#Includes
INKS			= -I$(CURDIR) -I$(MSG) -I$(LBB) -I$(LIBFT) -Ionline/ -I$(MLX_DIR)

ifeq ($(UNAME),Darwin)
	MLX_DIR		= minilibx_opengl
	MLX			= $(MLX_DIR)/libmlx.a
	URL			= https://cdn.intra.42.fr/document/document/31539/minilibx_opengl.tgz
	DEFS		=
	INKS		+= -I/usr/X11/include -I$(MLX_DIR)
	LINKS		+= -I/opt/homebrew/include -I/usr/X11/include -L/usr/X11/lib -framework OpenGL -framework AppKit
else ifeq ($(UNAME),Linux)
	MLX_DIR		= minilibx-linux
	MLX			= $(MLX_DIR)/libmlx_$(UNAME).a
	URL			= https://cdn.intra.42.fr/document/document/31538/minilibx-linux.tgz
	DEFS		=
	INKS		+= -I/usr/include
	LINKS		+= -lmlx_Linux -I$(MLX_DIR)
else
	UNAME = Error
endif

#source files (expected in the root folder)
SRCS_DIR		=
SRC_FILES		= main.c \
				lbb_data_length.c \
				lbb_get_data.c \
				lbb_init.c \
				lbb_read_data.c \
				lbb_write_data.c \
				lbb_to_msg.c \
				lbb_delete_lobby.c \
				\
				msg_data_length.c \
				msg_get_data.c \
				msg_get_pos_tar.c \
				msg_read_data.c \
				\
				msg_utils.c \
				\
				client.c \
				client_reciever.c client_sender.c \
				\
				server.c \
				server_reciever.c server_sender.c \
				\
				actions.c buffer_actions.c \
				msg_handler.c \
				\
				minigame.c \
				input_handling.c put_stuff.c \
				\
				convert_stuff.c free_stuff.c \
				ft_perror.c search_env.c \
				libft_extension.c \
				\
				printers.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

VPATH 			= $(MSG) $(LBB) \
				online/ \
				online/client/ online/server \
				minigame/ \
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

$(LIBFT)libft.a:
	@echo "${BOLD}compiling libft...${RESET}"
	@$(MAKE) all -C $(LIBFT) --quiet

$(NAME): $(LIBFT)libft.a $(MLX) $(OBJS)
	@echo "${BOLD}compiling the $(NAME)...${RESET}"
	$(CC) $(CFLAGS) $(OBJS_DIR)* $(LIBFT)libft.a $(MLX) -I$(INKS) $(LINKS) -o $(NAME)
	@echo "${LIGHT_GREEN}DONE${RESET}"

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MLX_DIR)" ./*

clean:
	@rm -f $(OBJS_DIR)* game test
	@$(MAKE) clean -C $(LIBFT) --quiet
fclean: clean
	@rm -rf $(OBJS_DIR)
	@$(MAKE) fclean -C $(LIBFT) --quiet

lre: clean all

re: fclean all
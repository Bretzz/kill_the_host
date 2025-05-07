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
LINKS			= -lpthread

#Includes
INKS			= -I$(CURDIR) -I$(MSG) -I$(LBB) -I$(LIBFT)

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
				client_reciever.c \
				\
				actions.c msg_handler.c \
				\
				convert_stuff.c free_stuff.c \
				ft_perror.c search_env.c\
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

$(LIBFT)/libft.a:
	@echo "${BOLD}compiling libft...${RESET}"
	@$(MAKE) all -C $(LIBFT) --quiet

$(NAME): $(LIBFT)/libft.a $(OBJS)
	@echo "${BOLD}compiling the $(NAME)...${RESET}"
	$(CC) $(CFLAGS) $(OBJS_DIR)* $(LIBFT)/libft.a $(LINKS) -o $(NAME)
	@echo "${LIGHT_GREEN}DONE${RESET}"

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MLX_DIR)" ./*

clean:
	@rm -f $(OBJS_DIR)* game minigame test
	@$(MAKE) clean -C $(LIBFT) --quiet
fclean: clean
	@rm -rf $(OBJS_DIR)
	@$(MAKE) fclean -C $(LIBFT) --quiet

lre: clean all

re: fclean all
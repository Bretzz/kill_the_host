NAME 		= main_program
LIBFT 		= libft/libft.a
HPC 		= hpc/hpc.a
INCLUDES 	= -Ilibft -Ihpc/include


all: $(LIBFT) $(HPC)
	cc -Wall -Wextra -Werror $(INCLUDES) -c main.c -o main.o 
	cc main.o $(HPC) $(LIBFT) -o $(NAME) $(INCLUDES)

$(LIBFT):
	@$(MAKE) -C libft

$(HPC):
	@$(MAKE) -C hpc

clean:
	rm -f $(NAME)
	@$(MAKE) -C libft clean
	@$(MAKE) -C hpc clean

fclean: clean
	rm -f $(LIBFT) $(HPC)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C hpc fclean

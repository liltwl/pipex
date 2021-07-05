NAME = pipex

CFLAGS = -O3 -Wall -Wextra -Werror

HEADER = pipex_bonus.h	pipex.h	get_next_line.h

CC = gcc

FIL_ = pipex.c	tools.c	tools2.c	exec.c

FIL_BNS = pipex_bonus.c	tools_bonus.c	tools_2_bonus.c	exec_bonus.c	get_next_line.c	

OBJ = $(FIL:.c=.o)

FIL = $(addprefix ./srcs/, $(FIL_))

FIL_B = $(addprefix ./bonus/, $(FIL_BNS))

all: $(NAME)

$(NAME): $(FIL)
	$(CC) $(CFLAGS) $(FIL) -o $(NAME)

bonus : fclean 
	$(CC) $(CFLAGS) $(FIL_B) -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

me:
	@echo $(NAME)
	@echo "#    #  ####   ####  #####   #    #  ####   ####  #####  "
	@echo "##   # #    # #    # #    #  ##   # #    # #    # #    # "
	@echo "# #  # #    # #    # #####   # #  # #    # #    # #####  "
	@echo "#  # # #    # #    # #    #  #  # # #    # #    # #    # "
	@echo "#   ## #    # #    # #    #  #   ## #    # #    # #    # "
	@echo "#    #  ####   ####  #####   #    #  ####   ####  #####  "

norm:
	norminette $(FIL) $(addprefix ./inc/, $(HEADER)) $(FIL_B)

leaks:
	leaks $(NAME) > leak
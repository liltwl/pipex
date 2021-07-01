NAME = pipex

CFLAGS = -O3 -Wall -Wextra -Werror

HEADER = pipex.h

CC = gcc

FIL = pipex.c	tools.c	tools2.c	exec.c

OBJ = $(FIL:.c=.o)


all: $(NAME)

$(NAME): $(FIL)
	$(CC) $(CFLAGS) $(FIL) -o $(NAME)


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
	norminette $(FIL) $(HEADER)

leaks:
	leaks $(NAME) > leak
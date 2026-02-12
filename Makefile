NAME = bin/minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

LIBDIR = ./libft/
LIB = ./libft/lib/libft.a

MAIN = ./main.c
MAIN_OBJ = $(MAIN:.c=.o)

INIT_SRC = init_src/init.c \
					 init_src/init_env.c \
					 init_src/env_lst_utils.c

INIT_OBJ = $(INIT_SRC:.c=.o)


all: $(NAME)

$(NAME): $(MAIN_OBJ) $(INIT_OBJ) $(LIB)
	mkdir -p bin
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(INIT_OBJ) $(LIB) -lreadline -o $(NAME)

$(LIB) :
	make -C $(LIBDIR)
 
.PHONY: all clean fclean re

clean:
	rm -f $(INIT_OBJ)
	rm -f $(MAIN_OBJ)
	make clean -C $(LIBDIR)

bin: all clean

fclean: clean
	rm -rf bin
	make fclean -C $(LIBDIR)

re: fclean all

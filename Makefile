NAME = bin/minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

LIBDIR = ./libft/
LIB = ./libft/lib/libft.a

MAIN = ./main.c
MAIN_OBJ = $(MAIN:.c=.o)

INIT_SRC = 	init_src/init_data.c \
			init_src/env_lst_utils.c \
			init_src/set_sig_term.c \
			init_src/copy_env.c \
			init_src/shell_exit.c
INIT_OBJ = $(INIT_SRC:.c=.o)


LEXER_SRC = lexer_src/init_token_utils.c \
			lexer_src/init_token.c \
			lexer_src/lexer_utils.c \
			lexer_src/lexer.c
LEXER_OBJ = $(LEXER_SRC:.c=.o)


#PARSER_SRC = 
#PARSER_OBJ = $(INIT_SRC:.c=.o)


#EXPAND_SRC = 
#EXPAND_OBJ = $(INIT_SRC:.c=.o)

#EXEC_SRC =
#EXEC_OBJ = $(INIT_SRC:.c=.o)

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(INIT_OBJ) $(LEXER_OBJ) $(LIB)
	mkdir -p bin
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(INIT_OBJ) $(LEXER_OBJ) $(LIB) -lreadline -o $(NAME)

$(LIB) :
	make -C $(LIBDIR)
 
.PHONY: all clean fclean re

clean:
	rm -f $(INIT_OBJ)
	rm -f $(MAIN_OBJ)
	rm -f $(LEXER_OBJ)
	make clean -C $(LIBDIR)

bin: all clean

fclean: clean
	rm -rf bin
	make fclean -C $(LIBDIR)

re: fclean all

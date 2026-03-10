NAME = bin/minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	# Mac
	RL_PATH = $(shell brew --prefix readline 2>/dev/null || echo "/opt/homebrew/opt/readline")
	RL_INC  = -I$(RL_PATH)/include
	RL_LIB  = -L$(RL_PATH)/lib -lreadline
else
	# Linux
	RL_INC  =
	RL_LIB  = -lreadline
endif

LIBDIR = ./libft/
LIB = ./libft/lib/libft.a

MAIN = ./main.c
MAIN_OBJ = $(MAIN:.c=.o)

INIT_SRC =	init_src/init_data.c \
						init_src/env_lst_utils.c \
						init_src/set_sig_term.c \
						init_src/copy_env.c \
						init_src/shell_exit.c \
						init_src/init_list.c \
						init_src/heredoc_mode.c
INIT_OBJ = $(INIT_SRC:.c=.o)


LEXER_SRC = lexer_src/init_token_lst_db_utils.c \
						lexer_src/init_token_utils.c \
						lexer_src/init_token.c \
						lexer_src/lexer_utils.c \
						lexer_src/lexer.c
LEXER_OBJ = $(LEXER_SRC:.c=.o)


PARSER_SRC = 	parser_src/init_cmd_lst_db_utils.c \
							parser_src/parser.c \
							parser_src/parser_utils.c \
							parser_src/check_error.c \
							parser_src/init_redir_lst_db_utils.c
PARSER_OBJ = $(PARSER_SRC:.c=.o)


EXPAND_SRC = 	expand_src/expand.c \
							expand_src/subtitute.c \
							expand_src/quote.c \
							expand_src/expand_utils.c \
							expand_src/split_expand.c
							
EXPAND_OBJ = $(EXPAND_SRC:.c=.o)

BUILD_SRC =		build_src/ft_cd.c \
							build_src/ft_echo.c \
							build_src/ft_pwd.c \
							build_src/ft_export.c \
							build_src/ft_unset.c \
							build_src/ft_env.c \
							build_src/ft_exit.c
BUILD_OBJ = $(BUILD_SRC:.c=.o)

EXEC_SRC =	exec_src/exec.c \
			exec_src/redir.c \
			exec_src/exec_utils.c \
			exec_src/exec2.c \
			exec_src/exec_utils2.c
EXEC_OBJ = $(EXEC_SRC:.c=.o)

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(INIT_OBJ) $(LEXER_OBJ) $(EXPAND_OBJ) $(PARSER_OBJ) $(BUILD_OBJ) $(EXEC_OBJ) $(LIB)
	mkdir -p bin
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(INIT_OBJ) $(LEXER_OBJ) $(EXPAND_OBJ) $(PARSER_OBJ) $(BUILD_OBJ) $(EXEC_OBJ)  $(LIB) $(RL_LIB) -o $(NAME)
	mkdir -p obj
	mv $(MAIN_OBJ) $(INIT_OBJ) $(LEXER_OBJ) $(EXPAND_OBJ) $(PARSER_OBJ) $(BUILD_OBJ) $(EXEC_OBJ) obj/

$(LIB) :
	make bonus -C $(LIBDIR)

.PHONY: all clean fclean re

clean:
	rm -rf obj
	make clean -C $(LIBDIR)

bin: all clean

val: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./bin/minishell

fclean: clean
	rm -rf bin
	make fclean -C $(LIBDIR)

re: fclean all
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
OBJ_DIR = obj

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    RL_PATH = $(shell brew --prefix readline 2>/dev/null || echo "/opt/homebrew/opt/readline")
    RL_INC  = -I$(RL_PATH)/include
    RL_LIB  = -L$(RL_PATH)/lib -lreadline
else
    RL_INC  = 
    RL_LIB  = -lreadline
endif

LIBDIR = ./libft/
LIB = ./libft/lib/libft.a

MAIN = main.c
INIT_SRC = init_src/init_data.c init_src/env_lst_utils.c init_src/set_sig_term.c \
           init_src/copy_env.c init_src/shell_exit.c init_src/init_list.c \
           init_src/heredoc_mode.c
LEXER_SRC = lexer_src/init_token_lst_db_utils.c lexer_src/init_token_utils.c \
            lexer_src/init_token.c lexer_src/lexer_utils.c lexer_src/lexer.c
PARSER_SRC = parser_src/init_cmd_lst_db_utils.c parser_src/parser.c \
             parser_src/parser_utils.c parser_src/check_error.c \
             parser_src/init_redir_lst_db_utils.c
EXPAND_SRC = expand_src/expand.c expand_src/subtitute.c expand_src/quote.c \
             expand_src/expand_utils.c expand_src/split_expand.c
BUILD_SRC = build_src/ft_cd.c build_src/ft_echo.c build_src/ft_pwd.c \
            build_src/ft_export.c build_src/ft_unset.c build_src/ft_env.c \
            build_src/ft_exit.c
EXEC_SRC = exec_src/exec.c exec_src/redir.c exec_src/exec_utils.c \
           exec_src/exec2.c exec_src/exec_utils2.c

SRC = $(MAIN) $(INIT_SRC) $(LEXER_SRC) $(PARSER_SRC) $(EXPAND_SRC) $(BUILD_SRC) $(EXEC_SRC)

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

VPATH = init_src:lexer_src:parser_src:expand_src:build_src:exec_src:.

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(RL_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(RL_INC) -c $< -o $@

$(LIB) :
	make bonus -C $(LIBDIR)

.PHONY: all clean fclean re

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBDIR)

val: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./$(NAME)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBDIR)

re: fclean all
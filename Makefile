NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RL_LIB = -lreadline

# Sources
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
EXEC_SRC = exec_src/exec.c exec_src/redir.c exec_src/exec_utils.c exec_src/exec2.c

# Objets (Correction du bug $ et notdir)
OBJ_FILES = $(notdir $(MAIN:.c=.o) $(INIT_SRC:.c=.o) $(LEXER_SRC:.c=.o) \
            $(PARSER_SRC:.c=.o) $(EXPAND_SRC:.c=.o) $(BUILD_SRC:.c=.o) $(EXEC_SRC:.c=.o))
OBJS = $(addprefix obj/, $(OBJ_FILES))

# Chemins pour que make trouve les .c
VPATH = init_src:lexer_src:parser_src:expand_src:build_src:exec_src:.

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C ./libft
	mkdir -p obj
	$(CC) $(CFLAGS) $(OBJS) ./libft/lib/libft.a $(RL_LIB) -o $(NAME)

obj/%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

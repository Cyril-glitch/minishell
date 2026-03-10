/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:09:00 by mtagand           #+#    #+#             */
/*   Updated: 2026/03/10 13:49:44 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

# define PATH_MAX 4096

# ifdef __APPLE__

void					rl_replace_line(const char *text, int clear_undo);
void					rl_clear_history(void);
# endif

// Couleurs Normales
# define RESET "\001\033[0m\002"
# define BLACK "\001\033[0;30m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define BLUE "\001\033[0;34m\002"
# define PURPLE "\001\033[0;35m\002"
# define CYAN "\001\033[0;36m\002"
# define WHITE "\001\033[0;37m\002"

// bold blue
# define B_BLUE "\001\033[1;34m\002"
// bold light red
# define B_L_RED "\001\033[1;91m\002"
// vert menthe doux
# define MINT "\001\033[38;5;121m\002"
// Rouge Corail Doux (Coral)
# define CORAL "\001\033[38;5;203m\002"
// Un Bleu Acier
# define STEEL "\001\033[38;5;110m\002"
// lavande
# define LAVENDER "\001\033[38;5;147m\002"
// ice blue
# define ICE_BLUE "\001\033[38;5;117m\002"

extern int				g_sig_status;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	D_REDIR_IN,
	D_REDIR_OUT,
	DOUBLE_PIPE
}						t_type;

typedef enum e_build
{
	ECHOO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	DFL,
	DFL2
}						t_build;

typedef struct s_redir
{
	t_type				type;
	char				*file;
	int					fd_heredoc;
	struct s_redir		*next;
	struct s_redir		*prev;
}						t_redir;

typedef struct s_redir_list
{
	t_redir				*head;
	t_redir				*tail;
	int					size;
}						t_redir_list;

typedef struct s_cmd
{
	char				**args;
	char				*way;
	t_redir_list		*redirs_list;
	int					is_build;
	t_build				build;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_cmd_list
{
	t_cmd				*head;
	t_cmd				*tail;
	int					size;
}						t_cmd_list;

typedef struct s_token
{
	char				*origin;
	char				*content;
	t_type				type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_token_list
{
	t_token				*head;
	t_token				*tail;
	int					size;
}						t_token_list;

typedef struct s_env_list
{
	char				*line;
	char				*key;
	char				*content;
	struct s_env_list	*next;
	struct s_env_list	*prev;
}						t_env_list;

typedef struct s_expand
{
	char				*prefix;
	char				*key;
	char				*val;
	char				*suffix;
	char				*cat;
	char				quote;
}						t_expand;

typedef struct s_prompt
{
	char				*user;
	char				*group;
	char				*pwd;
	char				*prompt;
}						t_prompt;

typedef struct s_data
{
	char				*line;
	int					fd_tmp;
	t_env_list			*env_list;
	t_token_list		*token_list;
	t_cmd_list			*cmd_list;
	struct sigaction	*sig_a;
	struct termios		*orig_termios;
	struct termios		*new_termios;
	t_expand			*expd;
	t_list				*expd_lst;
	int					last_exit_code;
	int					child;
	t_prompt			*prompt;
	pid_t				last_pid;
	char				**my_env;
	int					doc_line;
}						t_data;

// INIT
void					ft_interactive_mode(struct sigaction *sig_a,
							t_data *data);
void					ft_init_termios(struct termios *orig_termios,
							struct termios *new_termios);
t_data					*ft_init_data(int ac, char **av, char **env);
void					ft_add_env_list(t_data *data, char **env);
void					ft_add_token_list(t_data *data);
void					ft_add_cmd_list(t_data *data);
void					ft_add_expand(t_data *data);
void					ft_childmode(struct sigaction *sig_a, t_data *data);
void					ft_heredoc_mode(struct sigaction *sig_a, t_data *data);
void					ft_sigmute(struct sigaction *sig_a);

// INIT_ENV
t_env_list				*ft_new_env(char *str);
t_env_list				*ft_env_list(char **env, t_data *data);
void					ft_shlvl(t_env_list **env_list, t_data *data);
void					ft_my_env(t_env_list *env_list, t_data *data);

// ENV_LST_UTILS
void					ft_lstadd_back_env(t_env_list **lst, t_env_list *new);
void					ft_clear_node_env(t_env_list *node);
void					ft_lstclear_env(t_env_list **lst);
t_env_list				*ft_lstlast_env(t_env_list *lst);

// SHELL_EXIT
void					ft_shell_exit(t_data *data);
void					ft_free_data(t_data *data);
void					ft_shell_exit_hd(t_data *data, char *file);
void					ft_free_prompt(t_data *data);

// LEXER
void					ft_db_lstadd_front_token(t_token_list *token_list,
							t_token *new);
void					ft_db_lstadd_back_token(t_token_list *token_list,
							t_token *new);
void					ft_db_lstdelone_token(t_token *token,
							void (*del)(void *));
void					ft_db_lstclear_token(t_token_list *token_list,
							void (*del)(void *));
t_token					*ft_db_lstnew_token(void);
void					init_word(t_data *data, t_token *token, int *i);
void					init_pipe(t_data *data, t_token *token, int *i);
void					init_redir_in(t_data *data, t_token *token, int *i);
void					init_redir_out(t_data *data, t_token *token, int *i);
void					init_token(t_data *data, t_token *token, int *i);
void					swipe_space(char *str, int *i);
int						is_separator(char c);
void					ft_display_list_token(t_token_list *lst);
int						lexer(t_data *data);
void					nb_of_malloc(char *str, int *i, int *j, char quote);
void					copy_word(char *str, int *i, char quote,
							t_token *token);

// EXPAND
void					ft_expand(t_token_list *token_lst, t_env_list *env_lst,
							t_data *data);
void					ft_expd_zero(t_expand *expd);
int						ft_quote_status(t_expand *expd, char c);
void					ft_subtitute(char *s, t_token *token_lst,
							t_env_list *env_lst, t_data *data);
char					*ft_delquote(char *str);
int						ft_val_edge_case(char *str, t_expand *expd,
							t_data *data);
void					ft_split_expand(t_token_list *lst, t_data *data);
void					ft_expand_line(char **line, t_data *data);

// PARSER
void					ft_db_lstadd_front_cmd(t_cmd_list *cmd_list,
							t_cmd *new);
void					ft_db_lstadd_back_cmd(t_cmd_list *cmd_list, t_cmd *new);
void					ft_db_lstdelone_cmd(t_cmd *token, void (*del)(void *));
void					ft_db_lstclear_cmd(t_cmd_list *cmd_list,
							void (*del)(void *));
t_cmd					*ft_db_lstnew_cmd(void);
void					ft_display_list_cmd(t_cmd_list *lst);
int						parser(t_data *data);
int						is_redir(t_token *current);
int						is_build(t_cmd **cmd);
int						check_error(t_token_list *token_list);
void					ft_db_lstadd_front_redir(t_redir_list *redir_list,
							t_redir *new);
void					ft_db_lstadd_back_redir(t_redir_list *redir_list,
							t_redir *new);
void					ft_db_lstdelone_redir(t_redir *token,
							void (*del)(void *));
void					ft_db_lstclear_redir(t_redir_list *redir_list,
							void (*del)(void *));
t_redir					*ft_db_lstnew_redir(void);
void					ft_display_list_redir(t_redir_list *lst);

// BUILD IN
int						ft_cd(char **path, t_env_list *env_list, t_data *data);
void					ft_pwd(t_env_list *env_list);
int						ft_export(char **args, t_env_list **env_list,
							t_data *data);
int						ft_unset(char **args, t_env_list **env_list,
							t_data *data);
void					ft_del_env(t_env_list *todel, t_env_list **env_list);
t_env_list				*ft_key_hunter(char *args, t_env_list *env_list,
							t_data *data);
void					ft_echo(char **args);
void					ft_exit(t_cmd *cmd, t_data *data);
void					ft_env(char **args, t_env_list *env_list);
char					*ft_prompt_pwd(t_env_list *env_list, t_data *data);

// EXEC
void					exec(t_cmd *cmd, char **env, t_data *data);
void					redirection(t_cmd *cmd, t_data *data);
int						ft_tabclear(char **tab);
char					**parse_path(char **env);
char					*find_way_path(char **path_tab, char *cmd,
							t_data *data);
void					execut(t_data *data, char **env);
void					pipex(t_cmd *cmd, t_data *data, int *fd_pipe);
int						check_heredoc(t_cmd_list *cmd_list, t_data *data);

#endif

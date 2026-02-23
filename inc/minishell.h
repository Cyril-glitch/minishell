/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:09:00 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/23 11:35:47 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define  PATH_MAX 4096

# ifdef __APPLE__
    /* Ces fonctions sont dans la lib readline mais absentes des headers par défaut du Mac */
    void	rl_replace_line(const char *text, int clear_undo);
    void	rl_clear_history(void);
# endif

extern volatile sig_atomic_t	g_sig_status;

typedef enum e_type
{
	WORD,       // Pour ls, -l, file.txt
	PIPE,
	REDIR_IN,   // <
	REDIR_OUT,  // >
	D_REDIR_IN, // <<
	D_REDIR_OUT, // >>
	DOUBLE_PIPE
}								t_type;

typedef enum e_build
{
	ECHOO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}								t_build;

typedef struct s_redir
{
    t_type						type;
    char            			*file;
    struct s_redir  			*next;
    struct s_redir  			*prev;
}   							t_redir;

typedef struct s_redir_list
{
	t_redir						*head;
	t_redir						*tail;
	int							size;	
}								t_redir_list;

typedef struct s_cmd
{
    char          				**args;
	t_redir_list				*redirs_list;
	int							is_build;
	t_build						build;
    struct s_cmd 				*next;
	struct s_cmd				*prev;
} 								t_cmd;

typedef struct s_cmd_list
{
	t_cmd						*head;
	t_cmd						*tail;
	int							size;	
}								t_cmd_list;

typedef struct s_token
{
	char						*content;
	t_type						type;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

typedef struct s_token_list
{
	t_token						*head;
	t_token						*tail;
	int							size;
}								t_token_list;

typedef struct s_env_list
{
	char						*line;
	char						*key;
	char						*content;
	struct s_env_list			*next;
	struct s_env_list			*prev;
}								t_env_list;

typedef struct  s_expand
{
    char *prefix;
    char *key;
    char *val;
    char *suffix;
    char *cat;

    char quote;
} t_expand;

typedef struct s_data {
    char *line;
	int					fd_tmp;
    t_env_list      *env_list;
    t_token_list    *token_list;
	t_cmd_list		*cmd_list;
    struct sigaction	*sig_a;
    struct termios  *orig_termios;
    struct termios  *new_termios;
    t_expand *expd;
    t_list *expd_lst;
    int             last_exit_code;
} t_data;

//EXPAND
void ft_expand(t_token *token_lst, t_env_list *env_lst, t_data *data);
void ft_expd_zero(t_expand *expd);
int    ft_quote_status(t_expand *expd, char c);
void ft_subtitute(char *s, t_token *token_lst, t_env_list *env_lst, t_data *data);
char *ft_delquote(char *str);

//INIT
void	ft_init_signal(struct sigaction *sig_a);
void	ft_init_termios(struct termios *orig_termios, struct termios *new_termios);
t_data  *ft_init_data(int ac, char **av, char **env);
void    ft_add_env_list(t_data *data, char **env);
void    ft_add_token_list(t_data *data);
void	ft_add_cmd_list(t_data *data);
void  ft_add_expand(t_data *data);

//INIT_ENV
t_env_list						*ft_new_env(char *str);
t_env_list						*ft_env_list(char **env);

//ENV_LST_UTILS
void	ft_lstadd_back_env(t_env_list **lst,\
    t_env_list *new);
void							ft_clear_node_env(t_env_list *node);
void							ft_lstclear_env(t_env_list **lst);
t_env_list						*ft_lstlast_env(t_env_list *lst);
void							ft_printlst_env(t_env_list *lst);

//LEXER
void		ft_db_lstadd_front_token(t_token_list *token_list, t_token *new);
void		ft_db_lstadd_back_token(t_token_list *token_list, t_token *new);
void		ft_db_lstdelone_token(t_token *token, void (*del)(void*));
void		ft_db_lstclear_token(t_token_list *token_list, void (*del)(void*));
t_token		*ft_db_lstnew_token();
void		init_word(t_data *data, t_token *token, int *i);
void    	init_pipe(t_data *data, t_token *token, int *i);
void		init_redir_in(t_data *data, t_token *token, int *i);
void		init_redir_out(t_data *data, t_token *token, int *i);
void		init_token(t_data *data, t_token *token, int *i);
void		swipe_space(char *str, int *i);
int			is_separator(char c);
void		ft_display_list_token(t_token_list *lst);
int			lexer(t_data *data);
void    	nb_of_malloc(char *str, int *i, int *j, char quote);
void    	copy_word(char *str, int *i, char quote, t_token *token);

//SHELL_EXIT
void	ft_shell_exit(t_data *data);
void    ft_free_data(t_data *data);

//PARSER
void		ft_db_lstadd_front_cmd(t_cmd_list *cmd_list, t_cmd *new);
void		ft_db_lstadd_back_cmd(t_cmd_list *cmd_list, t_cmd *new);
void		ft_db_lstdelone_cmd(t_cmd *token, void (*del)(void*));
void		ft_db_lstclear_cmd(t_cmd_list *cmd_list, void (*del)(void*));
t_cmd		*ft_db_lstnew_cmd();
void		ft_display_list_cmd(t_cmd_list *lst);
int	    	parser(t_data *data);
int			is_redir(t_token *current);
int			check_error(t_token_list *token_list);
void		ft_db_lstadd_front_redir(t_redir_list *redir_list, t_redir *new);
void		ft_db_lstadd_back_redir(t_redir_list *redir_list, t_redir *new);
void		ft_db_lstdelone_redir(t_redir *token, void (*del)(void*));
void		ft_db_lstclear_redir(t_redir_list *redir_list, void (*del)(void*));
t_redir    	*ft_db_lstnew_redir();
void		ft_display_list_redir(t_redir_list *lst);

//BUILD IN
int  ft_cd(char *path,t_env_list *env_list, t_data *data);
void  ft_pwd(t_env_list *env_list);
void  ft_export(char **args, t_env_list **env_list, t_data *data);
void  ft_unset(char **args, t_env_list **env_list);
void ft_del_env(t_env_list *todel, t_env_list **env_list);
t_env_list *ft_key_hunter(char *args, t_env_list *env_list);
void ft_echo(char **args);

//EXEC
void    	exec(t_cmd *cmd, char **env, t_data *data);
void    	redirection(t_cmd *cmd, t_data *data);
int			ft_tabclear(char **tab);
char		**parse_path(char **env);
char		*find_way_path(char **path_tab, char *cmd, t_data *data);
void 		execut(t_data *data, char **env);

#endif

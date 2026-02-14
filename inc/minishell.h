/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:09:00 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/13 12:32:29 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <termios.h>

extern volatile sig_atomic_t	g_sig_status;

typedef enum e_type
{
    WORD,       // Pour ls, -l, "mon fichier"
    PIPE,       // |
    REDIR_IN,   // <
    REDIR_OUT,  // >
    D_REDIR_IN, // <<
    D_REDIR_OUT // >>
}								t_type;

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
    char						*var;
    char						*content;
    struct s_env_list			*next;
}								t_env_list;

typedef struct  s_expand
{
    char *prefix;
    char *val;
    char *suffixe;

    int quote;
    int d_quote;
} t_expand;

typedef struct s_data {
    char *line;
    t_env_list      *env_list;
    t_token_list    *token_list;
    struct sigaction	*sig_a;
    struct termios  *orig_termios;
    struct termios  *new_termios;
    int             last_exit_code;
} t_data;



//INIT
void	ft_init_signal(struct sigaction *sig_a);
void	ft_init_termios(struct termios *orig_termios, struct termios *new_termios);
t_data  *ft_init_data(int ac, char **av, char **env);

//COPY_ENV
t_env_list						*ft_new_env(char *str);
t_env_list						*ft_env_list(char **env);

//ENV_LST_UTILS
void	ft_lstadd_back_env(t_env_list **lst, t_env_list *new);
void							ft_clear_node_env(t_env_list *node);
void							ft_lstclear_env(t_env_list **lst);
t_env_list						*ft_lstlast_env(t_env_list *lst);
void							ft_printlst_env(t_env_list *lst);

//SHELL_EXIT
void	ft_shell_exit(t_data *data);
void    ft_free_data(t_data *data);

//LEXER
void	ft_db_lstadd_front(t_token_list *token_list, t_token *new);
void	ft_db_lstadd_back(t_token_list *token_list, t_token *new);
void	ft_db_lstdelone(t_token *token, void (*del)(void*));
void	ft_db_lstclear(t_token_list *token_list, void (*del)(void*));
t_token    *ft_db_lstnew();
void	init_word(char *str, t_token *token, int *i);
void    init_pipe(t_token *token, int *i);
void	init_redir_in(char *str, t_token *token, int *i);
void	init_redir_out(char *str, t_token *token, int *i);
void	init_token(char *str, t_token *token, int *i);
void	swipe_space(char *str, int *i);
int		is_separator(char c);
void	ft_display_list(t_token_list *lst);
void	lexer(char *str, t_token_list *token_list);

#endif

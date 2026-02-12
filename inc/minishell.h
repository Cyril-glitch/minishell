/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:09:00 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/11 11:21:43 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H


# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>


extern volatile  sig_atomic_t g_sig_status;

typedef enum e_type {
    WORD,         // Pour ls, -l, "mon fichier"
    PIPE,         // |
    REDIR_IN,     // <
    REDIR_OUT,    // >
    D_REDIR_IN,   // <<
    D_REDIR_OUT   // >>
} t_type;

typedef struct s_token {
    char            *content;
    t_type          type;
    struct s_token  *next;
    struct s_token  *prev;
} t_token;

typedef struct s_token_list {
    t_token         *head;
    t_token         *tail;
    int             size;
} t_token_list;

typedef struct  s_env_list {
    char *line;
    char *var;
    char *content;
    struct s_env_list *next;
} t_env_list;

//INIT
void  ft_shell_exit(t_token_list *list, t_env_list *env_list, struct termios orig_termios);
void  ft_init_signal(struct sigaction	*sig_a);
void  ft_termios(struct termios *orig_termios, struct termios *new_termios);

//INIT_ENV
t_env_list  *ft_new_env(char *str);
t_env_list *ft_env_list(char **env);

//ENV_LST_UTILS
void	ft_lstadd_back_env(t_env_list **lst, t_env_list *new);
void ft_clear_node_env(t_env_list *node);
void	ft_lstclear_env(t_env_list **lst);
t_env_list *ft_lstlast_env(t_env_list *lst);
void	ft_printlst_env(t_env_list	*lst);


#endif

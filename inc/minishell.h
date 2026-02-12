/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:09:00 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/12 13:52:59 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef enum e_type {
    WORD,         // Pour ls, "mon fichier"
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

typedef struct  s_env_copy {
    char *line;
    char *var;
    char *content;
    struct s_env_copy *next;
} t_env_copy;
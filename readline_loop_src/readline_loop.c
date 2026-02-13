/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:47:45 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/13 10:45:13 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_display_list(t_token_list *lst)
{
	t_token	*current;

	current = lst->head;
	while (current)
	{
		printf("%s -> ", current->content);
		current = current->next;
	}
	printf("NULL\n");
	current = lst->head;
	while (current)
	{
		printf("%u -> ", current->type);
		current = current->next;
	}
	printf("NULL\n");
	printf("size = %d\n", lst->size);
}

void	ft_db_lstadd_front(t_token_list *token_list, t_token *new)
{
	if (token_list->head == NULL)
	{
		token_list->head = new;
		token_list->tail = new;
	}
	else
	{
		new->next = token_list->head;
		token_list->head->prev = new;
		new->prev = NULL;
		token_list->head = new;
	}
	token_list->size++;
}

void	ft_db_lstadd_back(t_token_list *token_list, t_token *new)
{
	if (token_list->head == NULL)
	{
		ft_db_lstadd_front(token_list, new);
		return ;
	}
	new->prev = token_list->tail;
	token_list->tail->next = new;
	new->next = NULL;
	token_list->tail = new;
	token_list->size++;
}

void	ft_lstdelone(t_token *token, void (*del)(void*))
{
	del(token->content);
	free(token);
}

void	ft_db_lstclear(t_token_list *token_list, void (*del)(void*))
{
	t_token	*current;
	t_token	*tmp;

	current = token_list->head;
	tmp = current;
	while (current)
	{
		current = current->next;
		ft_lstdelone(tmp, del);
		tmp = current;
	}
	token_list->head = NULL;
	token_list->tail = NULL;
	token_list->size = 0;
}

t_token	*ft_db_lstnew()
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int is_separator(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}

void	init_word(char *str, t_token *token, int *i)
{
    int j;
    int k;
    
    j = 0;
    k = 0;
	while (!is_separator(str[*i + j]) && str[*i + j])
        j++;
	token->content = malloc(sizeof(char) * (j + 1));
	if (!token->content)
		return;
	j = 0;
    k = 0;
	while (!is_separator(str[*i + j - k]) && str[*i + j - k])
	{
        token->content[j] = str[*i];
		(*i)++;
		j++;
        k++;
	}
	token->content[*i] = '\0';
	token->type = WORD;
}

void    init_pipe(char *str, t_token *token, int *i)
{
    token->content = malloc(sizeof(char) * 2);
    if (!token->content)
        return;
    token->content[0] = '|';
    token->content[1] = '\0';
    (*i)++;
    token->type = PIPE;
}

void	init_redir_in(char *str, t_token *token, int *i)
{
    int j;
    
    j = 0;
	while (str[*i + j] == '<')
        j++;
	token->content = malloc(sizeof(char) * (j + 1));
    if (!token->content)
        return;
	j = 0;
	while (str[*i] == '<')
	{
        token->content[j] = str[*i];
		(*i)++;
		j++;
	}
	token->content[*i] = '\0';
	if (j == 1)
        token->type = REDIR_IN;
    if (j == 2)
        token->type = D_REDIR_IN;
}

void	init_redir_out(char *str, t_token *token, int *i)
{
    int j;
    
    j = 0;
	while (str[*i + j] == '>')
        j++;
	token->content = malloc(sizeof(char) * (j + 1));
	if (!token->content)
        return;
    j = 0;
	while (str[*i] == '>')
	{
        token->content[j] = str[*i];
		(*i)++;
		j++;
	}
	token->content[*i] = '\0';
	if (j == 1)
        token->type = REDIR_OUT;
    if (j == 2)
        token->type = D_REDIR_OUT;
}

void swipe_space(char *str, int *i)
{
    while (str[*i] == ' ')
        (*i)++;
}

void	init_head(char *str, t_token *token, int *i)
{
    swipe_space(str, i);
	if (!is_separator(str[*i]))
    {
        init_word(str, token, i);
        return;
    }
	if (str[*i] == '|')
    {
        init_pipe(str, token, i);
        return;
    }
    if (str[*i] == '<')
    {
        init_redir_in(str, token, i);
        return;
    }
    if (str[*i] == '>')
    {
        init_redir_out(str, token, i);
        return;
    }
}

void	lexer(char *str, t_token_list *token_list)
{
    int i;
    t_token *new_token;
    
    i = 0;
	new_token = ft_db_lstnew();
	token_list->head = new_token;
	token_list->tail = new_token;
	token_list->size = 1;
	init_head(str, token_list->head, &i);
    swipe_space(str, &i);
    while (str[i])
    {
        new_token = ft_db_lstnew();
        ft_db_lstadd_back(token_list, new_token);
        init_head(str, new_token, &i);
        swipe_space(str, &i);
    }
}

void	loop(char *str, t_token_list *token_list)
{
	while (str)
	{
		str = readline("losmakinos:~$ ");
		add_history(str);
		lexer(str, token_list);
        ft_display_list(token_list);
		ft_db_lstclear(token_list, free);
		free(str);
	}
}

int	main(void)
{
	char *s;
	t_token_list token_list;

	loop(s, &token_list);
}
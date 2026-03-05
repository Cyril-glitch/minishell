#include "../inc/minishell.h"

static t_token_list *ft_add_split_token_lst(void)
{
    t_token_list *new;

    new = malloc(sizeof(t_token_list));
    if (!new)
        return (NULL);
    new->head = NULL;
    new->tail = NULL;
    new->size = 0;
    return new;
}

static int	ft_q_status(char quote, char c)
{
	if (!quote && (c == '\'' || c == '\"'))
		return (c);
	else if (quote && c == quote)
		return (0);
	return (quote);
}

static void ft_splitoken(t_token *cur, char *str, t_token_list *newlst, t_data *data, char quote)
{
    t_token *new;
    char *tmp;
    int i;

    i = 0;
    new = ft_db_lstnew_token();
    if (!new)
        ft_shell_exit(data);
    while ((str[i] && str[i] != ' ') || quote == '\"')
        quote = ft_q_status(quote ,str[i++]);
    tmp = ft_substr(str,0,i);
    if (!tmp)
        ft_shell_exit(data);
    new->content = ft_delquote(tmp);
    new->type = cur->type;
    if (!new)
        ft_shell_exit(data);
    free(tmp);
    ft_db_lstadd_back_token(newlst, new);
    str += (i + (str[i] == ' '));
    if (*str)
        ft_splitoken(cur, str , newlst, data, quote);
}

void ft_split_expand(t_token_list *lst, t_data *data)
{
	t_token	*current;
    t_token_list *newlst;

    current = lst->head;
    newlst = ft_add_split_token_lst();
    if (!newlst)
        ft_shell_exit(data);
    while (current)
    {
        ft_splitoken(current, current->content, newlst, data, 0);
        current = current->next;
    }
	ft_db_lstclear_token(data->token_list , free);
    free(data->token_list);
    data->token_list = newlst;
}

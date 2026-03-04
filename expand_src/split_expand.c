#include "../inc/minishell.h"

int	ft_q_status(char quote, char c)
{
	if (quote && (c == '\'' || c == '\"'))
		return (c);
	else if (quote && c == quote)
		return (0);
	return (0);
}

static void ft_splitoken(char *str, t_token_list *newlst, t_data *data, char quote)
{
    int i;
    t_token *new;
    char *tmp;

    i = 0;
    new = ft_db_lstnew_token();
    if (!new)
        ft_shell_exit(data);
    while (str[i] && str[i] != ' ')
        quote = ft_q_status(quote ,str[i++]);
    if (quote != '\"')
    {
        tmp = ft_substr(str,0,i);
        new->content = ft_delquote(tmp);
        free(tmp);
        ft_db_lstadd_front_token(newlst, new);
    }
    if (str[i])
    {
        str += i;
        ft_splitoken(str, newlst, data, quote);
    }
}

void ft_split_expand(t_token_list *lst, t_data *data)
{
	t_token	*current;
    t_token_list *newlst;

    current = lst->head;
    newlst = NULL;
    while (current)
    {
        ft_splitoken(current->content, newlst, data, 0);
        current = current->next;
    }
	ft_db_lstclear_token(lst , free);
    lst = newlst;
}

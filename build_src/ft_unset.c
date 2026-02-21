#include "../inc/minishell.h"

t_env_list *ft_key_hunter(char *args, t_env_list *env_list)
{
    while (env_list)
    {
        if (ft_strcmp(args, env_list->key) == 0)
            return env_list;
        env_list = env_list->next;
    }
    return NULL;
}

void ft_del_env(t_env_list *todel, t_env_list **env_list)
{
    t_env_list *cur;
    t_env_list *prev;
    t_env_list *next;


    cur = *env_list;
    if (cur == todel && !cur->next)
    {
        ft_lstclear_env(env_list);
        return ;
    }
    prev = todel->prev;
    next = todel->next;
    free(todel);
    todel = NULL;
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;
}

void  ft_unset(char **args, t_env_list **env_list)
{
    int			i;
    t_env_list	*tmp;

    i = 1;
    tmp = NULL;
    while (args[i])
    {
        tmp = ft_key_hunter(args[i], *env_list);
        if (tmp)
            ft_del_env(tmp, env_list);
        i++;
    }
}

#include "../inc/minishell.h"

int    ft_valid_args(char *s)
{
    int i;

    i = 0;
    if(!ft_isalpha(s[i]) && s[i] != '_')
    {
        ft_putstr_fd("losmaquinos: export: \" ", 2);
        write(2, &s[i], 1);
        ft_putstr_fd(" \" : identifiant non valable\n", 2);
        return (0);
    }
    while (s[i])
    {
        if(!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '?' && s[i] != '=')
        {
            ft_putstr_fd("losmaquinos: export: \" ", 2);
            ft_putstr_fd(s, 2);
            ft_putstr_fd(" \" : identifiant non valable", 2);
            return (0);
        }
        i++;
    }
    return (1);
}

void  ft_export(char **args, t_env_list **env_list, t_data *data)
{
    int			i;
    t_env_list	*tmp;

    i = 1;
    tmp = NULL;
    if (!args[i])
    {
        ft_printlst_env(*env_list);
        return ;
    }
    while (args[i])
    {
        if (ft_valid_args(args[i]))
        {
            tmp = ft_new_env(args[i]);
            if (!tmp)
                ft_shell_exit(data);
            ft_lstadd_back_env(env_list, tmp);
        }
        i++;
    }
}

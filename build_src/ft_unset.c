void  ft_unset(char **args, t_env_list **env_list, t_data *data)
{
	int			i;
	t_env_list	*tmp;

	i = 1;
	env_list = NULL;
	tmp = NULL;
  if (!args[i])
  {
    ft_printlst_env(*env_list);
    return ;
  }
	while (args[i])
	{
		tmp = ft_new_env(args[i]);
		if (!tmp)
			return (ft_lstclear_env(env_list), (NULL));
		i++;
	}
}

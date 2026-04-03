/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:33:25 by mathis            #+#    #+#             */
/*   Updated: 2026/02/25 21:01:53 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_word(t_data *data, t_token *token, int *i)
{
	int		j;
	char	quote;

	j = 0;
	quote = 0;
	nb_of_malloc(data->line, i, &j, quote);
	token->content = malloc(sizeof(char) * (j + 1));
	if (!token->content)
		ft_shell_exit(data);
	copy_word(data->line, i, quote, token);
	token->content[j] = '\0';
	token->type = WORD;
}

void	init_pipe(t_data *data, t_token *token, int *i)
{
	int	j;

	j = 0;
	while (data->line[*i + j] == '|')
		j++;
	token->content = malloc(sizeof(char) * (j + 1));
	if (!token->content)
		ft_shell_exit(data);
	j = 0;
	while (data->line[*i] == '|')
	{
		token->content[j] = data->line[*i];
		(*i)++;
		j++;
	}
	token->content[j] = '\0';
	if (j == 1)
		token->type = PIPE;
	if (j >= 2)
		token->type = DOUBLE_PIPE;
}

void	init_redir_in(t_data *data, t_token *token, int *i)
{
	int	j;

	j = 0;
	while (data->line[*i + j] == '<')
		j++;
	token->content = malloc(sizeof(char) * (j + 1));
	if (!token->content)
		ft_shell_exit(data);
	j = 0;
	while (data->line[*i] == '<')
	{
		token->content[j] = data->line[*i];
		(*i)++;
		j++;
	}
	token->content[j] = '\0';
	if (j == 1)
		token->type = REDIR_IN;
	if (j >= 2)
		token->type = D_REDIR_IN;
}

void	init_redir_out(t_data *data, t_token *token, int *i)
{
	int	j;

	j = 0;
	while (data->line[*i + j] == '>')
		j++;
	token->content = malloc(sizeof(char) * (j + 1));
	if (!token->content)
		ft_shell_exit(data);
	j = 0;
	while (data->line[*i] == '>')
	{
		token->content[j] = data->line[*i];
		(*i)++;
		j++;
	}
	token->content[j] = '\0';
	if (j == 1)
		token->type = REDIR_OUT;
	if (j >= 2)
		token->type = D_REDIR_OUT;
}

void	init_token(t_data *data, t_token *token, int *i)
{
	swipe_space(data->line, i);
	if (!is_separator(data->line[*i]))
		init_word(data, token, i);
	if (data->line[*i] == '|')
		init_pipe(data, token, i);
	if (data->line[*i] == '<')
		init_redir_in(data, token, i);
	if (data->line[*i] == '>')
		init_redir_out(data, token, i);
}

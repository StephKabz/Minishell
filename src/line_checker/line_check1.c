/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_check1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:39:48 by kingstephan       #+#    #+#             */
/*   Updated: 2025/09/25 05:25:56 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parse.h"

int	is_valid_redirection(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return(0);
	current = tokens;
	while(current)
	{
		if (current->type == TOKEN_HEREDOC
			|| current->type == TOKEN_REDIR_APPEND
			|| current->type == TOKEN_REDIR_IN
			|| current->type == TOKEN_REDIR_OUT)
		{
			if (current->next == NULL 
				|| current->next->type != TOKEN_WORD)
				return (0);
		}
		current = current->next;
	}
	return (1);
}

int	consecutive_pipes(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (0);
	current = tokens;
	while (current && current->next)
	{
		if (current->type == TOKEN_PIPE)
			if (current->next->type == TOKEN_PIPE)
				return (0);
		current = current->next;
	}
	return (1);
}

int	consecutive_redirections(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (0);
	current = tokens;
	while (current && current->next)
	{
		if (current->type == TOKEN_HEREDOC
			|| current->type == TOKEN_REDIR_APPEND
			|| current->type == TOKEN_REDIR_IN
			|| current->type == TOKEN_REDIR_OUT)
		{
			if (current->next->type == TOKEN_HEREDOC
			|| current->next->type == TOKEN_REDIR_APPEND
			|| current->next->type == TOKEN_REDIR_IN
			|| current->next->type == TOKEN_REDIR_OUT)
				return (0);
		}
		current = current->next;
	}
	return (1);
}

int	valid_pipe_position(t_token *tokens)
{
	t_token *current;

	if (!tokens)
		return (0);
	current = tokens;
	if (current->type == TOKEN_PIPE)
		return (0);
	while (current)
	{
		if (current->type == TOKEN_PIPE && current->next == NULL)
			return (0);
		current = current->next;
	}
	return (1);
}

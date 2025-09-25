/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:05:02 by kingstephan       #+#    #+#             */
/*   Updated: 2025/09/25 05:19:20 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parse.h"

int	nb_args(t_token **token)
{
	int	count;
	t_token	*tmp;

	count = 0;
	tmp = *token;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_command	*init_cmd(int word_count)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = malloc(sizeof(char *) * (word_count + 1));
	if (!new_cmd->argv)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->append = -1;
	new_cmd->heredoc = -1;
	new_cmd->next = NULL;
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->delimiter = NULL;
	new_cmd->redir = NULL;
	return (new_cmd);
}

char	*safe_ft_strdup(char *s, t_command **cmd_lst)
{
	char	*dup;

	if (!s)
		return (NULL);
	dup = ft_strdup(s);
	if (!dup)
	{
		if (cmd_lst && *cmd_lst)
		{
			free_cmd_list(*cmd_lst);
			*cmd_lst = NULL;
		}
		return (NULL);
	}
	return (dup);
}

void	clean_cmd_argv(char **argv, int count)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (i < count)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

int	is_redirection(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN)
		return (1);
	else if (token->type == TOKEN_HEREDOC)
		return (1);
	else if (token->type == TOKEN_REDIR_OUT)
		return (1);
	else if (token->type == TOKEN_REDIR_APPEND)
		return (1);
	else
		return (0);
}

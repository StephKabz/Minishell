/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:48:48 by kingstephan       #+#    #+#             */
/*   Updated: 2025/09/25 05:24:43 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parse.h"

t_token	*new_token(char *string, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->string = ft_strdup(string);
	if (!new_token->string)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*last;

	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_token;
}

void	free_token(t_token *head)
{
	t_token	*tmp;

	if (head == NULL)
		return ;
	while (head)
	{
		tmp = head->next;
		free(head->string);
		free(head);
		head = tmp;
	}
}

int	emit_token(t_token **head, char *str, int type)
{
	t_token	*new;

	new = new_token(str, type);
	if (!new)
		return (0);
	add_token(head, new);
	return (1);
}

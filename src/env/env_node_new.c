/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouali <ebouali@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:39:35 by ebouali           #+#    #+#             */
/*   Updated: 2025/09/03 19:39:38 by ebouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_node_new(const char *name, const char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	if (value == NULL)
		node->value = NULL;
	else
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free(node->name);
			free(node);
			return (NULL);
		}
	}
	node->next = NULL;
	return (node);
}

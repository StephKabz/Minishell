/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:49:00 by kingstephan       #+#    #+#             */
/*   Updated: 2025/09/25 05:24:27 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parse.h"

static void free_redir_list(t_redir *redir)
{
    t_redir *tmp;
    while (redir) {
        tmp = redir->next;
        if (redir->target) free(redir->target);
        if (redir->fd > STDERR_FILENO) close(redir->fd);
        free(redir);
        redir = tmp;
    }
}

void	free_cmd_list(t_command *cmd)
{
	int	i;
	t_command	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
		}
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->delimiter)
			free(cmd->delimiter);
		if (cmd->redir)
			free_redir_list(cmd->redir);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}

int	calculate_total_size(char *str, t_env *env)
{
	int		total;
	int		i;

	if (!str)
		return (0);
	i = 0;
	total = 0;
	while (str[i])
	{
		if (str[i] == '$' && (var_start_ok(str[i + 1]) || str[i + 1] == '?'))
			total += get_var_len(str, &i, env);
		else
		{
			total++;
			i++;
		}
	}
	return (total + 1);
}

void	add_var_value(char *str, char *result, int *i, int *j, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		k;

	var_name = extract_var_name(str, i);
	if (!var_name)
		return ;
	var_value = get_var_value(var_name, env);
	if (var_value)
	{
		k = 0;
		while (var_value[k])
			result[(*j)++] = var_value[k++];
	}
	free(var_name);
	free(var_value);
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	result = malloc((calculate_total_size(str, env)) * sizeof(char));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && check_special_dollar_case(str, i))
			result[j++] = str[i++];
		else if (str[i] == '$' && (var_start_ok(str[i + 1]) || str[i + 1] == '?'))
			add_var_value(str, result, &i, &j, env);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

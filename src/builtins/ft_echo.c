/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:28:36 by ebouali           #+#    #+#             */
/*   Updated: 2025/09/23 02:19:21 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include "../../include/minishell.h"

static int	is_n_flag(const char *s)
{
	if (!s || s[0] != '-' || s[1] != 'n' || s[2] != '\0')
		return (0);
	return (1);
	//Cette logique accepte -nnn ou -nnnn comme des flags -n valides, mais bash n'accepte que -n exactement.
}

static void	print_args(char **argv, int i)
{
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
}

int	ft_echo(char **argv, t_env **env)
{
	int	i;
	int	new_line;

	(void)env;
	i = 1;
	new_line = 1;
	while (argv[i] && is_n_flag(argv[i]))
	{
		new_line = 0;
		i++;
	}
	print_args(argv, i);
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}

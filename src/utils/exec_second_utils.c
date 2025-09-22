/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_second_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouali <ebouali@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:46:25 by ebouali           #+#    #+#             */
/*   Updated: 2025/09/03 19:46:26 by ebouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_fds(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		perror("minishell: dup2");
	if (dup2(out, STDOUT_FILENO) == -1)
		perror("minishell: dup2");
	close(in);
	close(out);
}

int	run_builtin_in_parent(t_command *cmd, t_env **env)
{
	int	save_in;
	int	save_out;
	int	status;

	if (save_fds(&save_in, &save_out) == -1)
		return (g_exit_code = 1);
	if (apply_redirections(cmd, env) == -1)
	{
		restore_fds(save_in, save_out);
		return (g_exit_code);
	}
	status = exec_builtin(cmd->ARGS, env);
	restore_fds(save_in, save_out);
	return (status);
}

char	**build_child_envp(t_env *env)
{
	char	**envp;

	envp = env_to_envp(env);
	if (!envp)
		ft_putstr_fd("minishell: env alloc error\n", 2);
	return (envp);
}

void	child_exec_sequence(t_command *cmd, t_env *env, char *path,
		int path_owned)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (apply_redirections(cmd, &env) == -1)
	{
		if (g_exit_code)
			exit(g_exit_code);
		else
			exit(1);
	}
	execve(path, cmd->ARGS, env_to_envp(env));
	perror("minishell");
	if (path_owned)
		free(path);
	exit(126);
}

int	check_slash_cmd_fs(const char *name)
{
	struct stat	st;

	if (access(name, F_OK) != 0)
	{
		print_error(name, ": No such file or directory");
		g_exit_code = 127;
		return (-1);
	}
	if (stat(name, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_error(name, ": Is a directory");
		g_exit_code = 126;
		return (-1);
	}
	if (access(name, X_OK) != 0)
	{
		print_error(name, ": Permission denied");
		g_exit_code = 126;
		return (-1);
	}
	return (0);
}

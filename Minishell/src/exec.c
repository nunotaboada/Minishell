/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:54:21 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/03 18:54:21 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

void	childprocess(t_cmds *cmd, int *fd)
{
	if (cmd->infd != STDIN_FILENO)
	{
		if (dup2(cmd->infd, STDIN_FILENO) == -1)
			g_ex_status = 1;
		close(cmd->infd);
	}
	if (cmd->outfd != STDOUT_FILENO)
	{
		if (dup2(cmd->outfd, STDOUT_FILENO) == -1)
			g_ex_status = 1;
		close(cmd->outfd);
	}
	else if (cmd->next)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			g_ex_status = 1;
	}
	close(fd[1]);
	close(fd[0]);
}

void	makefork(t_shell *sh, t_cmds *cmd, int *fd)
{
	sh->pid = fork();
	if (sh->pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		g_ex_status = 1;
	}
	if (sh->pid == 0)
	{
		childprocess(cmd, fd);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!checkbuiltins(cmd))
			execve(cmd->path, cmd->cmd_line, sh->envp);
		else if (checkbuiltins(cmd) > 0)
			builtins(cmd, sh);
		free(sh->cmd_line);
		free_all(sh);
		exit(g_ex_status);
	}
}

void	parentprocess(t_cmds *cmd, int *fd)
{
	close(fd[1]);
	if (cmd->next && (cmd->next->infd == STDIN_FILENO))
		cmd->next->infd = fd[0];
	else
		close(fd[0]);
	if (cmd->infd > 2)
		close(cmd->infd);
	if (cmd->outfd > 2)
		close(cmd->outfd);
}

/*lembrar de libertar a path*/
int	execcmd(t_shell *sh)
{
	t_cmds	*cmd;
	int		fd[2];

	cmd = sh->cmds;
	while (cmd)
	{
		sh->fork = 0;
		if (cmd->cmd_line && checkbuiltins(cmd) < 0 && !cmd->next)
			builtins(cmd, sh);
		else if (cmd->cmd_line && cmd->infd != -2 && cmd->outfd != -2)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, signal_quit);
			cmd->path = search_path(sh, cmd);
			if (pipe(fd) == -1)
			{
				g_ex_status = 1;
				return (1);
			}
			is_fork(sh, cmd, fd);
			parentprocess(cmd, fd);
		}
		cmd = cmd->next;
	}
	return (0);
}

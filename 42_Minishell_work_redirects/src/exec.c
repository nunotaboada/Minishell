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

extern int g_ex_status;

int is_dir(const char *path)
{
    DIR *dir;

	dir = opendir(path);
    if (dir)
    {
        closedir(dir);
        return (1);
    }
    return (0);
}

int is_fork(t_shell *sh, t_cmds *cmd, int *fd)
{
	if (cmd->infd == -1 || cmd->outfd == -1)
		return (0);
	if (cmd->path && !access(cmd->path, X_OK) && !is_dir(cmd->path))
	{

		makeFork(sh, cmd, fd);
		sh->proc++;
	}
	if (!cmd->path && ft_strchr(cmd->cmd_line[0], '/'))
		errorFork("minishell: ", cmd->cmd_line[0],": No such file or directory\n", 127);
	else if (!cmd->path && !ft_strchr(cmd->cmd_line[0], '/'))
		errorFork("minishell: ", cmd->cmd_line[0],": command not found\n", 127);
	else if (is_dir(cmd->path))
		errorFork("minishell: ", cmd->cmd_line[0],": Is directory\n", 126);
	else if (access(cmd->path, X_OK) == -1)
		errorFork("minishell: ", cmd->cmd_line[0],": Permission denied\n", 126);
	return (1);
}

void makeFork(t_shell *sh, t_cmds *cmd, int *fd)
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
            // Processo filho
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!checkBuiltins(cmd))
			execve(cmd->path, cmd->cmd_line, sh->envp);
		else if (checkBuiltins(cmd) > 0)
			builtins(cmd, sh);
		exit(g_ex_status);
	}
}

 /*lembrar de libertar a path*/
int execCmd (t_shell *sh)
{
	t_cmds *cmd;
	int wstatus;
	int fd[2];

	cmd = sh->cmds;
	while (cmd)
	{
		if (cmd->cmd_line && checkBuiltins(cmd) < 0 && !cmd->next)
			builtins(cmd, sh);
		else if (cmd->cmd_line && cmd->infd != -2 && cmd->outfd != -2)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			cmd->path = search_path(sh, cmd);
			printf("Path: %s\n", cmd->path);
			if (pipe(fd) == -1)
			{
				g_ex_status = 1;
				return (1);
			}
			is_fork(sh, cmd, fd);
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
		cmd = cmd->next;
	}
	printf("processos %d\n", sh->proc);
	waitpid(sh->pid, &wstatus, 0);
	while (sh->proc)
		{
			wait(0);
			sh->proc--;
		}
	printf("processos %d\n", sh->proc);
	// falta o wait que vá buscar o exit status
	return (0);
}
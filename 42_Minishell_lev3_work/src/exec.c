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
/*O código depois do fork só é executado pelo processo parent, neste caso o incremento, ou entra em caso de erro numa das outras condições*/
int is_fork(t_shell *sh, t_cmds *cmd, int *fd)
{
	if (cmd->infd == -1 || cmd->outfd == -1)
		return (0);
	if (cmd->path && !access(cmd->path, X_OK) && !is_dir(cmd->path))
	{

		makeFork(sh, cmd, fd);
		sh->proc++; // diz o nº de processos criados. Posso vir a precisar de uma flag
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
	int fd[2];

	cmd = sh->cmds;
	while (cmd)
	{
		if (cmd->cmd_line && checkBuiltins(cmd) < 0 && !cmd->next)
			builtins(cmd, sh);
		else if (cmd->cmd_line && cmd->infd != -2 && cmd->outfd != -2) // vem dos redirecs não foi possível o acesso aos ficheiros feito com acess F_OK verifica se existe e R_OK se é possível escreve.
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
			// if (!is_fork(sh, cmd, fd))
			// 	return (1);
			is_fork(sh, cmd, fd);
			// close(fd[0]);
			// close(fd[1]);
			close(fd[1]);	
			if (cmd->next && (cmd->next->infd == STDIN_FILENO))
				cmd->next->infd = fd[0];
				// dup2(fd[0], STDIN_FILENO);
			else
				close(fd[0]);

// Não esquecer que estamos num ciclo while e que só o parente faz esta parte do código, isto significa que em cada ciclo e para cada chil process são fechados os fs - pipe correspondente.
// A verificação condicional if (cmd->next && (cmd->next->infd == STDIN_FILENO)) verifica se existe um próximo comando (cmd->next) e se o descritor de arquivo de entrada desse próximo comando (cmd->next->infd) é igual a STDIN_FILENO (o descritor de arquivo padrão para entrada).

// Se ambas as condições forem verdadeiras, significa que o próximo comando está esperando a entrada padrão. Nesse caso, o descritor de arquivo de entrada desse próximo comando é substituído pelo descritor fd[0]. Isso é feito para redirecionar a saída do comando atual (processo pai) para a entrada do próximo comando.
		}
		cmd = cmd->next;
	}
	printf("processos %d\n", sh->proc);
	while (sh->proc)
		{
			wait(0);
			sh->proc--;
		}
	printf("processos %d\n", sh->proc);
	// falta o wait que vá buscar o exit status
	return (0);
}
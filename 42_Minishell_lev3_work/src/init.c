/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:28:59 by nsoares-          #+#    #+#             */
/*   Updated: 2023/05/10 11:01:01 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_ex_status;

// t_cmds *cmds;
// 	t_token *head_token;
//     char *cmd_line;
// 	int		i; // posição na string
// 	int		wd_lim; // posição na string
// 	int		dquotes; // double quotes
// 	int		squotes; // single quotes
// 	int		pipeOp;// nº of pipes
// 	int		proc;// nº de processos criados
// 	char		**envp;
// 	pid_t		pid;

void init(int ac, char **av, char **envp, t_shell *shell)
{
    (void)ac;
    (void)av;
	shell->i = 0;
	shell->pid = 0;
	shell->proc = 0;
	shell->wd_lim = 0;
	shell->pipeOp = 0;
	shell->dquotes = 0;
	shell->squotes = 0;
    shell->cmd_line = NULL;
	shell->cmds = NULL;
	shell->head_token = NULL;
	shell->envp = mtr_dup(envp);
	if (!(shell->envp))
		exit(g_ex_status = 1);
	shell->pid = 0;
}
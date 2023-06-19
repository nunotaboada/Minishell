/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:12:57 by nsoares-          #+#    #+#             */
/*   Updated: 2023/05/09 13:22:50 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ex_status;

int	is_operator(char c)
{
	if (c == 60)
		return (1);
	if (c == 62)
		return (1);
	if (c == 124)
		return (1);
	return (0);
}

void	ft_wait(t_shell *sh)
{
	int			wstatus;

	if (waitpid(sh->pid, &wstatus, 0) != -1)
	{
		if (WIFSIGNALED(wstatus))
			wstatus += 128;
		if (sh->fork)
			g_ex_status = wstatus;
		if (g_ex_status == 130)
			ft_putchar_fd('\n', STDOUT_FILENO);
		sh->proc--;
	}
	while (sh->proc)
	{
		wait(0);
		sh->proc--;
	}
	if (g_ex_status > 255)
		g_ex_status = g_ex_status / 255;
	printf("processos %d\n", sh->proc);
}

int	operators(t_shell *sh)
{
	t_token			*start;

	start = NULL;
	start = sh->head_token;
	while (start)
	{
		if (start->type == 'O')
		{
			if (ft_strcmp(start->word, "|") == 0)
			{
				if (start->next == NULL || start->prev == NULL \
				|| start->next->type == 'O')
				{
					g_ex_status = 2;
					printf("minishell: syntax error near unexpected token \
					'%s'\n", start->word);
					return (1);
				}
			}
			else if (ft_strcmp(start->word, "<") == 0 || ft_strcmp(start->word, \
			">") == 0 || ft_strcmp(start->word, ">>") == 0)
			{
				if (start->next == NULL )
				{
					g_ex_status = 2;
					printf("minishell: syntax error near unexpected \
					token `newline\'\n");
					return (1);
				}
				if (start->next->type == 'O')
				{
					g_ex_status = 2;
					printf("minishell: syntax error near unexpected token \
					'%s'\n", start->word);
					return (1);
				}
			}
			else if (start->prev == NULL && ft_strcmp(start->word, "<<") == 0)
			{
				g_ex_status = 2;
				printf("minishell: syntax error near unexpected \
				token '%s'\n", start->word);
				return (1);
			}
		}
		start = start->next;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;

	init(ac, av, envp, &shell);
	while (1)
	{
		signals();
		shell.cmd_line = show_prompt(&shell);
		if (!shell.cmd_line)
			continue ;
		add_history(shell.cmd_line);
		// words(&shell);
		if (!words(&shell))
			execcmd(&shell);
		ft_wait(&shell);
		free(shell.cmd_line);
		free_listtoken(shell.head_token);
		free_listcmd(shell.cmds);
		shell.head_token = NULL;
		shell.cmds = NULL;
	}
	free_all(&shell);
	return (0);
}

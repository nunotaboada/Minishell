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

int  g_ex_status;

int is_operator(char c)
{
	{
	if (c == 60) 		// <
		return (1);
	if (c == 62)		// >
		return (1);
	if (c == 124) 		// |
		return (1);
	return (0);
	}
}

/*Podem existir mais condições de erro, coloquei o cqso se a seguir ao pipe não tem elemento, caso se queira alterar tem de ser aqui*/
int operators(t_shell *sh)
{
    t_token	*start;

	start = NULL;
	start = sh->head_token;
	while (start)
	{
		if (start->type == 'O')
		{
			if (start->next == NULL || start->prev == NULL || start->next->type == 'O' \
			|| (start->prev == NULL && ft_strcmp(start->word, "<<") != 0)) // alteração
			{
				g_ex_status = 2;
				printf("minishell: syntax error near unexpected token '%s'\n",
					start->word);
				return (1);
			}
		}
		start = start->next;
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
    t_shell shell;
    
    init(ac, av, envp, &shell);
    while (1)
    {
        signals();
        shell.cmd_line = show_prompt(&shell);
        if (!shell.cmd_line)
           continue;
        add_history(shell.cmd_line);
		// words(&shell);
        if (!words(&shell))
			execCmd(&shell);
        free(shell.cmd_line);
		free_listtoken(shell.head_token);
		free_listcmd(shell.cmds);
		// free_listcmds(sh->cmds);
        shell.head_token = NULL;
		shell.cmds = NULL;
    }
    free_all(&shell);
    return (0);
}

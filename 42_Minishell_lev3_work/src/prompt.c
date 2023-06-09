/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:57:00 by nsoares-          #+#    #+#             */
/*   Updated: 2023/05/17 11:43:16 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_ex_status;


void	free_all(t_shell *sh)
{
	if (!sh)
		return ;
	mtr_free(sh->envp);
	free_listtoken(sh->head_token);
	free_listcmds(sh->cmds);
    sh->cmds = NULL;
    sh->head_token = NULL;
	sh = NULL;
}

char *show_prompt(t_shell *sh)
{
    char *line;
    char *str;
    
    line = readline("minishell$ ");
    if (!line)
    {
        printf("exit\n");
        clear_history();
        free_all(sh);
        free(line);
        exit(0);
    }
    str = ft_strtrim(line, " \t");
    if (str[0] == '\0')
    {
        free(str);
        str = NULL;
    }
    free(line);
    return (str);
}

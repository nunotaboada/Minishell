/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:57:50 by nsoares-          #+#    #+#             */
/*   Updated: 2023/05/16 15:47:10 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int built_echo(t_cmds *cmds)
{
    int i;
    int n_flag;

    n_flag = 0;
    i = 1;
    while (cmds->cmd_line[i] != NULL && ft_strcmp(cmds->cmd_line[i], "-n") == 0) 
    {
        n_flag = 1;
        i++;
    }
    if (cmds->cmd_line[i] != NULL)
    {
        printf("%s", cmds->cmd_line[i]);
        i++;
    }
    while (cmds->cmd_line[i] != NULL)
    {
        printf(" %s", cmds->cmd_line[i]);
        i++;
    }
    if (n_flag == 0)
        printf("\n");
    return (g_ex_status = 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:24:09 by nsoares-          #+#    #+#             */
/*   Updated: 2023/05/16 15:05:40 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int args_numbers(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '-' || str[i] == '+')
            i++;
        if (!ft_isdigit(str[i]))
            return (1);
        i++;
    }
    return (0);
}

int built_exit(t_cmds *cmds)
{
    int nb_args;
    int exit_status;

    nb_args = nb_of_args(cmds);
    if (nb_of_args(cmds) > 2 && args_numbers(cmds->cmd_line[1]) == 0)
    {
        printf("bash: exit: too many arguments\n");
        exit_status = 1;
        return (g_ex_status = exit_status);
    }
    printf("exit\n");
    if (nb_args == 2)
    {
        if (nb_args == 2 && args_numbers(cmds->cmd_line[1]) == 0)
            g_ex_status = ft_atoi(cmds->cmd_line[1]); 
        else if (args_numbers(cmds->cmd_line[1]) == 1)
        {
            printf("bash: exit: %s: numeric argument required\n", cmds->cmd_line[1]);
            exit_status = 2;
            exit(g_ex_status = exit_status);
        }
    } 
    exit(g_ex_status);
}
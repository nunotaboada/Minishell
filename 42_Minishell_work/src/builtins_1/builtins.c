/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 23:36:22 by nsoares-          #+#    #+#             */
/*   Updated: 2023/06/07 15:33:46 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int builtins(t_cmds *cmds, t_shell *shell)
{
    if (ft_strcmp(cmds->cmd_line[0], "echo") == 0)
        built_echo(cmds);
    else if (ft_strcmp(cmds->cmd_line[0], "cd") == 0)
        built_cd(cmds, shell);
    else if (ft_strcmp(cmds->cmd_line[0], "pwd") == 0)
        built_pwd();
    else if (ft_strcmp(cmds->cmd_line[0], "env") == 0)
        built_env(shell);
    else if (ft_strcmp(cmds->cmd_line[0], "export") == 0)
        built_export(shell, cmds);
    else if (ft_strcmp(cmds->cmd_line[0], "unset") == 0)
        built_unset(cmds, shell);
    else if (ft_strcmp(cmds->cmd_line[0], "exit") == 0)
        built_exit(cmds);
    else
        return (-1);
    return (0);
}
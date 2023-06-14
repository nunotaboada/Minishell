/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:20:03 by nsoares-          #+#    #+#             */
/*   Updated: 2023/06/07 15:24:52 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redirect_output(char *filename) 
{
    int fd;
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) 
    {
        printf("minishell: %s: ", filename);
        printf("No such file or directory");
        return (g_ex_status = 1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (g_ex_status = 0);
}

int redirect_append(char *filename)
{
    int fd;
    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (fd == -1) 
    {
        printf("minishell: %s: ", filename);
        printf("No such file or directory");
        return (g_ex_status = 1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (g_ex_status = 0);
}

int redirect_input(char *filename)
{
    int fd;
    fd = open(filename, O_RDONLY);
    if (fd == -1) 
    {
        printf("minishell: %s: ", filename);
        printf("No such file or directory");
        return (g_ex_status = 1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (g_ex_status = 0);
}

int check_redir(t_cmds *cmds)
{
    for (int i = 0; cmds->cmd_line[i] != NULL; i++)
    {
        if (ft_strcmp(cmds->cmd_line[i], ">") == 0)
        {
            redirect_output(cmds->cmd_line[i + 1]);
            cmds->cmd_line[i] = NULL;
            cmds->cmd_line[i + 1] = NULL;
            return 1;
        }
        else if (ft_strcmp(cmds->cmd_line[i], ">>") == 0)
        {
            redirect_append(cmds->cmd_line[i + 1]);
            cmds->cmd_line[i] = NULL;
            cmds->cmd_line[i + 1] = NULL;
            return 1;
        }
        else if (ft_strcmp(cmds->cmd_line[i], "<") == 0)
        {
            redirect_input(cmds->cmd_line[i + 1]);
            // Remover os argumentos de redirecionamento do comando
            cmds->cmd_line[i] = NULL;
            cmds->cmd_line[i + 1] = NULL;
            return 1;
        }
    }
    return 0;
}

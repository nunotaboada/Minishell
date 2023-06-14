/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:20:03 by nsoares-          #+#    #+#             */
/*   Updated: 2023/06/13 03:43:42 by nmoreira         ###   ########.fr       */
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
    return (0);
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
    return (0);
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
    return (0);
}

int redirect_input_heredoc(char *delimeter)
{
    char *buffer;
    int fd[2];

    pipe(fd);
    while (1)
    {
        //signals();
        buffer = readline("> ");
        if (!buffer)
        {
            free(buffer);
            break ;
        }   
        if (ft_strcmp(buffer, delimeter) == 0)
        {
            free(buffer);
            break ;
        }
        ft_putendl_fd(buffer, fd[1]);
    }
    close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
    return (0);
}

int check_redir(t_cmds *cmds) // parse redirects
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
            cmds->cmd_line[i] = NULL;
            cmds->cmd_line[i + 1] = NULL;
            return 1;
        }
        else if (ft_strcmp(cmds->cmd_line[i], "<<") == 0)
        {
            redirect_input_heredoc(cmds->cmd_line[i + 1]);
            // Remover os argumentos de redirecionamento do comando
            cmds->cmd_line[i] = NULL;
            cmds->cmd_line[i + 1] = NULL;
            return 1;
        }
    }
    return 0;
}

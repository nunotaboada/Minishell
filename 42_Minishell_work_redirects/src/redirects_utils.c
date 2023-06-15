/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:29:10 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/12 18:29:10 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_ex_status;

char *dirPath(t_shell *sh) // devolve o directório onde vamos colocar o file
{
	char *path;
	char *tmp;

	path = NULL;
	tmp = NULL;
	tmp = get_env("PWD", sh->envp);
	path = ft_strjoin(tmp, "/");
	tmp = NULL;
	return (path);
}

char *fullPath(char *path, t_token *token) // devolve a path incluindo o nome do file 
{
	char *allPath;

	allPath = NULL;
	allPath = ft_strjoin(path, token->word);
	return (allPath);
}

static int redHeredoc(char *delimeter)
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

int	parse_redirecs(t_shell *sh, t_cmds *node, t_token *token)
{
	if (ft_strcmp(token->word, ">") == 0
		|| ft_strcmp(token->word, ">>") == 0)
		return (redOut(sh, node, token->next));
	if (ft_strcmp(token->word, "<") == 0)
		return (redIn(sh, node, token->next));
	if (ft_strcmp(token->word, "<<") == 0)
		return (redHeredoc(token->next->word));
	return (0);
}

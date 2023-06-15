/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecr_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:20:02 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/14 16:20:02 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_ex_status;

int	fileIn(char *allPath, t_cmds *node, t_token *token)
{
	if (access(allPath, F_OK) == 0)
	{
		if (access(allPath, R_OK) == 0)
		{
			node->infd = open(allPath, O_RDONLY, 0644); // dá -1 se falhar
			return (0);
		}
		node->infd = -2;
		errorMinishell("minishell: ", token->word, ": Permission denied");
		g_ex_status = 1;
		return (1);
	}
	node->infd = -2;
	g_ex_status = 1;
	errorMinishell("minishell: ", token->word, ": No such file or directory");
	return (1);
}

int openFileRedirIn(char *path, t_cmds *node, t_token *token)
{
	DIR		*dir;
	char	*allPath;
	int		i;

	i = 0;
	allPath = NULL;
	dir = opendir(path);
	allPath = fullPath(path, token);
	free(path);
	i = fileIn(allPath, node, token);
	closedir(dir);
	free(allPath);
	return (i);
}

int redIn (t_shell *sh, t_cmds *node, t_token *token) // verifica se é possível aceder ao dir onde iremos colocar o file
{
	char *path;

	path = NULL;
	path = dirPath(sh);
	if  (node->infd != STDIN_FILENO && node->infd != -1 && node->infd != -2)
		close(node->infd);
	if (access(path, F_OK)) // verifica se o dir onde vamos colocar o file exite
	{	
		if (access(path, R_OK))
			return (openFileRedirIn(path, node, token));
		free (path);
		node->infd = -2;
		g_ex_status = 1;
		errorMinishell("minishell: ", token->word, ": Permission denied");
		return (1);
	}
	free(path);
	node->outfd = -2;
	g_ex_status = 1;
	errorMinishell("minishell: ", token->word, ": No such file or directory");
	return (1);
}
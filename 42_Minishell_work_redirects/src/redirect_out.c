/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:04:39 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/14 18:04:39 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_ex_status;

int fileOut(char *allPath, t_cmds *node, t_token *token)
{
	if (is_dir(allPath) == 1)
	{
		node->outfd = -2;
		errorMinishell("minishell: ", token->word, ": Is a dir");
		g_ex_status = 1;
		return (1);
	}
	if (access(allPath, F_OK) == 0) // para o caso de o ficheiro já existir
	{
		if (access(allPath, W_OK) == 0)
		{
			if (ft_strcmp(token->prev->word, ">>") == 0)
				node->outfd = open(allPath, O_CREAT | O_RDWR | O_APPEND, 0644);
			else
				node->outfd = open(allPath, O_CREAT | O_RDWR | O_TRUNC, 0644);
			return (0);
		}
		node->outfd = -2;
		errorMinishell("minishell: ", token->word, ": Permission denied");
		g_ex_status = 1;
		return (1);
	}
	if (ft_strcmp(token->word, ">>") == 0)
		node->outfd = open(allPath, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		node->outfd = open(allPath, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (0);
}

int openFileRedirOut(char *path, t_cmds *node, t_token *token)
{
	DIR		*dir;
	char	*allPath;
	int		i;

	i = 0;
	allPath = NULL;
	dir = opendir(path);
	allPath = fullPath(path, token);
	free(path);
	i = fileOut(allPath, node, token);
	closedir(dir);
	free(allPath);
	return (i);
}

int redOut (t_shell *sh, t_cmds *node, t_token *token) // verifica se é possível aceder ao dir onde iremos colocar o file
{
	char *path;

	path = NULL;
	path = dirPath(sh);
	if  (node->outfd != STDOUT_FILENO && node->outfd != -1 && node->outfd != -2)
		close(node->outfd);
	if (access(path, F_OK)) // verifica se o dir onde vamos colocar o file exite
		return (openFileRedirOut(path, node, token));
	free(path); // só executa se naõa tiver acesso o file logo temos de fazer free
	node->outfd = -2;
	g_ex_status = 1;
	errorMinishell("minishell: ", token->word, ": No such file or directory");
	return (1);
}

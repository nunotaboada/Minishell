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

char *fullPath(char *path, t_token *token)
{
	char *allPath;

	allPath = NULL;
	allPath = ft_strjoin(path, token->word);
	return (allPath);
}

int fileOut(char *allPath, t_cmds *node, t_token *token)
{
	if (is_dir(allPath) == 1)
	{
		n->out_file = -2;
		errorMinishell("minishell: ", token->word, ": Is a dir", 1)
		return (1);
	}
	if (access(allPath, F_OK) == 0) // para o caso de o ficheiro já existir
	{
		if (access(allPath, W_OK) == 0)
		{
			if (ft_strcmp(token->prev->word, ">>") == 0)
				n->out_file = open(allPath, O_CREAT | O_RDWR | O_APPEND, 0644);
			else
				n->out_file = open(allPath, O_CREAT | O_RDWR | O_TRUNC, 0644);
			return (0);
		}
		n->out_file = -2;
		errorMinishell("minishell: ", token->word, ": Permission denied", 1)
		return (1);
	}
	if (ft_strcmp(token->word, ">>") == 0)
		n->out_file = open(allPath, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		n->out_file = open(allPath, O_CREAT | O_RDWR | O_TRUNC, 0644);
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
	allPath = get_filepathname(path, token);
	free(path);
	i = fileOut(allPath, node, token);
	closedir(dir);
	free(allPath);
	return (i);
}

int redOut (t_shell *sh, t_cmds *node, t_token *token) // verifica se é possível aceder ao dir fornecido pela path
{
	char *path;
	int 

	path = NULL;
	path = dirPath(sh);
	if  (node->outfd != STDOUT_FILENO && node->outfd != -1 /
	node->outfd != -2)
		close(node->infd);
	if (access(path, F_OK))
		return (openFileRedirOut(path node, token));
	node->outfd = -2;
	return (errorMinishell("minishell: ", token->word, ": No such file or directory", 1));
}

int	parse_redirecs(t_shell *sh, t_cmds *node, t_token *token)
{
	if (ft_strcmp(token->word, ">") == 0
		|| ft_strcmp(token->word, ">>") == 0)
		return (redOut(sh, node, token->next));
	if (ft_strcmp(token->word, "<") == 0)
		return (redin(sh, node, token->next));
	if (ft_strcmp(token->word, "<<") == 0)
		return (redHeredoc(node, token->next->word));
	return (0);
}

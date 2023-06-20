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

extern int	g_ex_status;

char	*dirpath(t_shell *sh)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = NULL;
	tmp = get_env("PWD", sh);
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, "/");
	free(tmp);
	return (path);
}

char	*fullpath(char *path, t_token *token)
{
	char	*allpath;

	allpath = NULL;
	allpath = ft_strjoin(path, token->word);
	return (allpath);
}

static int	redheredoc(char *delimeter)
{
	char		*buffer;
	int			fd[2];

	pipe(fd);
	while (1)
	{
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

int	parse_redirecs(t_cmds *node, t_token *token)
{
	if (ft_strcmp(token->word, ">") == 0 \
	|| ft_strcmp(token->word, ">>") == 0)
		return (fileout(node, token->next));
	if (ft_strcmp(token->word, "<") == 0)
		return (filein(node, token->next));
	if (ft_strcmp(token->word, "<<") == 0)
		return (redheredoc(token->next->word));
	return (0);
}

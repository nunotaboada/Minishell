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

int	parse_redirecs(t_shell *sh, t_cmds *node, t_token *token)
{
	if (ft_strcmp(token->word, ">") == 0 \
	|| ft_strcmp(token->word, ">>") == 0)
		return (fileout(node, token->next));
	if (ft_strcmp(token->word, "<") == 0)
		return (filein(node, token->next));
	if (ft_strcmp(token->word, "<<") == 0)
		return (checkheredoc(sh, node, token->next->word));
	return (0);
}

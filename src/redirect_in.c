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

extern int	g_ex_status;

int	check_file_access(t_cmds *node, t_token *token)
{
	if (access(token->word, F_OK) == 0)
	{
		if (access(token->word, R_OK) == 0)
		{
			node->infd = open(token->word, O_RDONLY, 0644);
			return (0);
		}
		node->infd = -2;
		errorminishell("minishell: ", token->word, ": Permission denied");
		g_ex_status = 1;
		return (1);
	}
	else
	{
		node->infd = -2;
		errorminishell("minishell: ", token->word, \
		": No such file or directory\n");
		g_ex_status = 1;
		return (1);
	}
}

int	filein(t_cmds *node, t_token *token)
{
	if (is_dir(token->word) == 1)
	{
		node->outfd = -2;
		errorminishell("minishell: ", token->word, ": Is a dir\n");
		g_ex_status = 1;
		return (1);
	}
	return (check_file_access(node, token));
}

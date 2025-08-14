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

extern int	g_ex_status;

int	fileout(t_cmds *node, t_token *token)
{
	if (is_dir(token->word) == 1)
	{
		node->outfd = -2;
		errorminishell("minishell: ", token->word, ": Is a dir\n");
		g_ex_status = 1;
		return (1);
	}
	if (ft_strcmp(token->prev->word, ">>") == 0)
		node->outfd = open(token->word, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		node->outfd = open(token->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (0);
}

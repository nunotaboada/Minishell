/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:07:51 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/05 19:07:51 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

void	lexer_op(t_shell *sh)
{
	token_node(sh, 'N');
	if (sh->cmd_line[sh->i] == 60 || sh->cmd_line[sh->i] == 62)
	{
		if (sh->cmd_line[sh->i + 1] \
		&& sh->cmd_line[sh->i] == sh->cmd_line[sh->i + 1])
			sh->i += 2;
		else
			sh->i++;
	}
	else
		sh->i++;
	token_node(sh, 'O');
}

void	spaces(t_shell *sh)
{
	char	*temp;

	temp = NULL;
	if (sh->i - sh->wd_lim)
	{
		temp = ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim));
		node(sh, temp);
	}
	while (sh->cmd_line[sh->i] == ' ')
		sh->i++;
	sh->wd_lim = sh->i;
	free(temp);
}

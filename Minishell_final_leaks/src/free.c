/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 03:38:31 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/10 03:38:31 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_shell *sh)
{
	if (!sh)
		return ;
	mtr_free(sh->envp);
	// free(sh->cmd_line);
	free_listtoken(sh->head_token);
	free_listcmds(sh->cmds);
	sh->cmds = NULL;
	sh->head_token = NULL;
	sh = NULL;
}

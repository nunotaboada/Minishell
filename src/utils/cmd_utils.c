/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:34:12 by nmoreira          #+#    #+#             */
/*   Updated: 2023/05/21 11:34:12 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_listcmds(t_cmds *list)
{
	t_cmds		*current;

	if (!list)
		return ;
	current = list;
	while (list != NULL)
	{
		current = list->next;
		free(list);
		list = current;
	}
	list = NULL;
}

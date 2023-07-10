/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 03:27:36 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/20 03:27:36 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

static int	checkpipeoperator(t_token *start)
{
	if (ft_strcmp(start->word, "|") == 0)
	{
		if (start->next == NULL || start->prev == NULL \
		|| start->next->type == 'O')
		{
			g_ex_status = 2;
			printf("minishell: syntax error near unexpected token '%s'\n", \
			start->word);
			return (1);
		}
	}
	return (0);
}

static int	checkredirectionoperators(t_token *start)
{
	if (ft_strcmp(start->word, "<") == 0 || ft_strcmp(start->word, ">") == 0 \
	|| ft_strcmp(start->word, ">>") == 0)
	{
		if (start->next == NULL)
		{
			g_ex_status = 2;
			printf("minishell: syntax error near unexpected token `newline\'\n");
			return (1);
		}
		if (start->next->type == 'O')
		{
			printf("minishell: syntax error near unexpected token '%s'\n", \
			start->word);
			return (g_ex_status = 2);
		}
	}
	else if ((start->prev == NULL || start->next == NULL) \
	&& ft_strcmp(start->word, "<<") == 0)
	{
		g_ex_status = 2;
		printf("minishell: syntax error near unexpected token '%s'\n", \
		start->word);
		return (1);
	}
	return (0);
}

int	operators(t_shell *sh)
{
	t_token	*start;

	start = NULL;
	start = sh->head_token;
	while (start)
	{
		if (start->type == 'O')
		{
			if (checkpipeoperator(start))
				return (1);
			else if (checkredirectionoperators(start))
				return (1);
		}
		start = start->next;
	}
	return (0);
}

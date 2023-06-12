/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:07:59 by nmoreira          #+#    #+#             */
/*   Updated: 2023/05/14 20:07:59 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_ex_status;

int is_operator(char c)
{
	{
	if (c == 60) 		// <
		return (1);
	if (c == 62)		// >
		return (1);
	if (c == 124) 		// |
		return (1);
	return (0);
	}
}

void lexer_op(t_shell *sh)
{
	token_node(sh, 'N');
	if (sh->cmd_line[sh->i] == 60 || sh->cmd_line[sh->i] == 62)
	{
		if (sh->cmd_line[sh->i + 1] && sh->cmd_line[sh->i] == sh->cmd_line[sh->i + 1])
			sh->i += 2;
		else
			sh->i++;
	}
	else
		sh->i++;
	token_node(sh, 'O');
}

void lexer_word(t_shell *sh)
{
	if (sh->i - sh->wd_lim)
		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
	// while (sh->cmd_line[sh->i] == ' ')
	// 	sh->i++;
	sh->wd_lim = sh->i;
	sh->i++;
}

int div_input(t_shell *sh)
{
	sh->i = 0;
	sh->wd_lim = 0;
	// printf("teste1\n");
	while (sh->cmd_line[sh->i] != '\0')
	{
		if (sh->cmd_line[sh->i] == '\'' || sh->cmd_line[sh->i] == '\"')
		{
			// printf("teste2\n");
			if (detectarAspas(sh))
			{
				// free_listtoken(sh->head_token); estou a libertar nas aspas
				return (1); // estava exit (1);
			}
			// printf("%d\n", sh->i);
		}
		else if (is_operator(sh->cmd_line[sh->i]))
			lexer_op(sh);
		else if (sh->cmd_line[sh->i] == ' ')
		 	lexer_word(sh);
		else
			sh->i++;
	}
	// printf("%d\n", sh->i);
	if (sh->i - sh->wd_lim)
		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
	return (0);
}

int words(t_shell *sh)
{
	if (div_input(sh))
	{
		g_ex_status = 2;
		return (1);
	}
	if (operators(sh))
		return (1);
	// if (expand(sh))
	// 	return (1);
	return (0);
}
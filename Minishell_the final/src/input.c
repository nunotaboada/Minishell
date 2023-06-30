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
	if (sh->i - sh->wd_lim)
		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
	while (sh->cmd_line[sh->i] == ' ')
		sh->i++;
	sh->wd_lim = sh->i;
}

int	div_input(t_shell *sh)
{
	bool	daspas;
	bool	d_s_aspas;

	daspas = false;
	d_s_aspas = false;
	sh->i = 0;
	sh->wd_lim = 0;
	sh->pipeop = 0;
	while (sh->cmd_line[sh->i] != '\0')
	{
		if (sh->cmd_line[sh->i] == '\"')
			daspas = !daspas;
		if (sh->cmd_line[sh->i] == '\'')
			d_s_aspas = !d_s_aspas;
		if (sh->cmd_line[sh->i] == ' ' && !daspas && !d_s_aspas)
			spaces(sh);
		else if (is_operator(sh->cmd_line[sh->i]))
			lexer_op(sh);
		else
			sh->i++;
	}
	if (sh->i - sh->wd_lim)
		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
	return (0);
}

static int	div_words(t_shell *sh)
{
	if (checkdaspas(sh))
		return (1);
	if (!verificaraspas(sh))
	{
		error_quotes('\'');
		return (1);
	}
	if (div_input(sh))
		return (1);
	printf("after div words\n");
	print_list(sh);
	if (!checkaspas2(sh))
		rmvaspas(sh);
	return (0);
}

int	words(t_shell *sh)
{
	if (div_words(sh))
	{
		g_ex_status = 2;
		return (1);
	}
	printf("after remove aspas\n");
	print_list(sh);
	if (operators(sh))
		return (1);
	if (expand(sh))
		return (1);
	if (parser(sh))
		return (1);
	fill_index(sh);
	print_cmds(sh);
	return (0);
}

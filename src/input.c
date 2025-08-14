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

static void	process_word(t_shell *sh)
{
	char	*temp;

	temp = NULL;
	if (sh->i - sh->wd_lim)
	{
		temp = ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim));
		node(sh, temp);
		free(temp);
	}
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
		if (sh->cmd_line[sh->i] == ' ' && daspas == false && d_s_aspas == false)
			spaces(sh);
		else if (is_operator(sh->cmd_line[sh->i]) && daspas == false \
		&& d_s_aspas == false)
			lexer_op(sh);
		else
			sh->i++;
	}
	process_word(sh);
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
	if (operators(sh))
		return (1);
	if (expand(sh))
		return (1);
	if (parser(sh))
		return (1);
	fill_index(sh);
	return (0);
}

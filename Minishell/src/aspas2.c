/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aspas2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 04:58:42 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/20 04:58:42 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

static int	check_quotes(const char *cmd_line, char quote_type)
{
	int		i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] == quote_type)
			in_quotes = !in_quotes;
		i++;
	}
	if (in_quotes)
	{
		error_quotes(quote_type);
		return (1);
	}
	return (0);
}

int	checkdaspas(t_shell *sh)
{
	int		result;

	result = check_quotes(sh->cmd_line, '\"');
	if (result != 0)
		return (result);
	result = check_quotes(sh->cmd_line, '\'');
	if (result != 0)
		return (result);
	return (0);
}

/*para controlar a situação "'ls"'*/
bool	verificaraspas(t_shell *sh)
{
	int		i;
	int		count_s_aspas;
	int		count_d_aspas;
	bool	d_s_aspas;

	i = 0;
	count_d_aspas = 0;
	count_s_aspas = 0;
	d_s_aspas = false;
	while (sh->cmd_line[i] != '\0')
	{
		if (sh->cmd_line[i] == '\'')
		{
			count_s_aspas++;
			d_s_aspas = !d_s_aspas;
		}
		else if (sh->cmd_line[i] == '\"' && !d_s_aspas)
			count_d_aspas++;
		i++;
	}
	return (count_s_aspas % 2 == 0 && count_d_aspas % 2 == 0);
}

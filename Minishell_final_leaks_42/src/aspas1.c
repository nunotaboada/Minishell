/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aspas1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:00:37 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/23 19:00:37 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

/* faz o controlo de "" e '' */
static int	countsinglequotes(const char *cmd_line)
{
	int		i;
	int		count;

	i = 1;
	count = 0;
	while (cmd_line[i] && cmd_line[i] != ' ')
	{
		if (cmd_line[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

static int	countdoublequotes(const char *cmd_line)
{
	int		i;
	int		count;

	i = 1;
	count = 0;
	while (cmd_line[i] && cmd_line[i] != ' ')
	{
		if (cmd_line[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

static int	ft_strlenaspas(const char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0' && s[a] != ' ')
		a++;
	return (a);
}

int	checkaspas2(t_shell *sh)
{
	int		len;
	int		count;

	len = 0;
	count = 0;
	len = ft_strlenaspas(sh->cmd_line);
	if (len >= 2)
	{
		if (sh->cmd_line[0] == '\'')
			count = countsinglequotes(sh->cmd_line);
		else if (sh->cmd_line[0] == '\"')
			count = countdoublequotes(sh->cmd_line);
	}
	if (count + 1 == len)
		return (1);
	return (0);
}

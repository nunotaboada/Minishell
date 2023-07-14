/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:20:14 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/25 11:20:14 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

static char	*get_rest1(t_shell *sh, char *temp, int start)
{
	char	*rest1;

	rest1 = NULL;
	while (temp[sh->i] != '\"' && temp[sh->i] != '\0')
		sh->i++;
	if (sh->i > start)
		rest1 = ft_substr(temp, start, sh->i - start);
	return (rest1);
}

static char	*handle_double_quotes(t_shell *sh, char *temp)
{
	int		start;
	char	*env;
	char	*rest1;

	sh->i++;
	start = sh->i;
	env = NULL;
	rest1 = NULL;
	sh->dquotes = !sh->dquotes;
	rest1 = get_rest1(sh, temp, start);
	env = checkenv(rest1, sh);
	free(rest1);
	if (temp[sh->i] == '\"')
	{
		sh->dquotes = !sh->dquotes;
		sh->i++;
	}
	if (env)
		return (env);
	return (NULL);
}

static char	*handle_expansion(t_shell *sh, char *temp, char *expansion, int i)
{
	char	*env;

	env = NULL;
	if (end_varpos(temp, i + 1) < (int)ft_strlen(temp))
		expansion = ft_substr(temp, i, end_varpos(temp, i + 1) - i);
	else
		expansion = ft_substr(temp, i, end_varpos(temp, i + 1) - i);
	if (ft_strcmp(expansion, "$?") == 0)
	{
		free(expansion);
		sh->i += 2;
		return (ft_itoa(g_ex_status));
	}
	if ((ft_strcmp(expansion, "$") == 0))
	{
		sh->i++;
		return (expansion);
	}
	if (ft_strlen(expansion))
		env = get_env(expansion + 1, sh);
	free(expansion);
	return (env);
}

char	*doexp(t_shell *sh, char *temp)
{
	int		i;
	char	*expansion;
	char	*env;

	i = 0;
	expansion = NULL;
	env = NULL;
	if (temp[sh->i] == '\"')
		return (handle_double_quotes(sh, temp));
	i = sh->i;
	expansion = handle_expansion(sh, temp, expansion, i);
	if (env)
	{
		sh->i = end_varpos(temp, i + 1);
		return (env);
	}
	sh->i = end_varpos(temp, i + 1);
	return (expansion);
}

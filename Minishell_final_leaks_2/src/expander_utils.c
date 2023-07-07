/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:02:07 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/20 17:02:07 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

char	*ft_result(char *str, char *env)
{
	char	*result;

	result = NULL;
	if (str && env)
	{
		result = ft_strjoin(str, env);
		free(str);
		free(env);
	}
	else if (str)
	{
		result = ft_strdup(str);
		free(str);
	}
	else if (env)
	{
		result = ft_strdup(env);
		free(env);
	}
	if (!result)
		return (NULL);
	else
		return (result);
}

static char	*extract_quotes(char *temp, t_shell *sh, int start)
{
	char	*before;
	char	*quotes;
	char	*result;

	before = NULL;
	quotes = NULL;
	result = NULL;
	if (sh->i > start)
		before = ft_substr(temp, start, sh->i - start);
	sh->i++;
	start = sh->i;
	while (temp[sh->i] != '\'')
		sh->i++;
	sh->i++;
	if (sh->i > start)
		quotes = ft_substr(temp, start, sh->i - start - 1);
	result = ft_result(before, quotes);
	return (result);
}

static char	*extract_left(char *temp, t_shell *sh, int start)
{
	char	*left;

	left = NULL;
	if (sh->i > start)
		left = ft_substr(temp, start, sh->i - start);
	return (left);
}

char	*restexp(t_shell *sh, char *temp)
{
	char	*left;
	char	*result;
	char	*final;
	int		start;

	left = NULL;
	result = NULL;
	final = NULL;
	start = sh->i;
	while (temp[sh->i] != '\0' && temp[sh->i] != '$' && temp[sh->i] != '\"')
	{
		if (temp[sh->i] == '\'')
		{
			result = extract_quotes(temp, sh, start);
			start = sh->i;
		}
		else
			sh->i++;
	}
	if (sh->i > start)
		left = extract_left(temp, sh, start);
	final = ft_result(result, left);
	return (final);
}

char	*allword(t_shell *sh, char *temp)
{
	char	*rest;
	char	*parsed;
	char	*expansion;

	rest = NULL;
	parsed = restexp(sh, temp);
	expansion = doexp(sh, temp);
	if (expansion && parsed)
	{
		rest = ft_strjoin(parsed, expansion);
		free(parsed);
		free(expansion);
	}
	else if (parsed)
	{
		rest = ft_strdup(parsed);
		free(parsed);
	}
	else if (expansion)
	{
		rest = ft_strdup(expansion);
		free(expansion);
	}
	return (rest);
}

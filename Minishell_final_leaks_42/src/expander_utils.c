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

int	end_varpos(char *s, int pos)
{
	int		len;

	len = ft_strlen(s);
	while (pos < len)
	{
		if (s[pos] == '$' || s[pos] == '\'' \
		|| s[pos] == '\"' || s[pos - 1] == '?' || s[pos] == '\0')
			return (pos);
		pos++;
	}
	return (len);
}

static char	*ft_result(char *str, char *env)
{
	char	*result;

	result = NULL;
	if (str && env)
		result = ft_strjoin(str, env);
	else if (str)
		result = ft_strdup(str);
	else if (env)
		result = ft_strdup(env);
	if (!result)
		return (NULL);
	else
		return (result);
}

/* tive que retirar free(&data) no if e no fim por naõ ser endereço heap*/
char	*checkenv(char *str, t_shell *sh)
{
	char		*word;
	char		*conc;
	t_datamini	data;

	if (!str)
		return (NULL);
	initdatamini(&data);
	word = NULL;
	conc = NULL;
	while (str[data.i] != '\0')
	{
		initcicle(str, &data);
		data.rest = get_rest(str, data.start, data.i);
		if (str[data.i] == '$' && str[data.i + 1] == '\0')
		{
			conc = ft_result(data.rest, "$");
			word = concate(word, conc);
			free(conc);
			free(data.rest);
			return (word);
		}
		data.env = process_env_variable(str, &data, sh);
		conc = ft_result(data.rest, data.env);
		word = concate(word, conc);
		free(conc);
		free(data.env);
		free(data.rest);
	}
	return (word);
}

char	*restexp(t_shell *sh, char *temp)
{
	char	*left;
	int		start;

	left = NULL;
	start = sh->i;
	while (temp[sh->i] != '\0' && temp[sh->i] != '$' && temp[sh->i] != '\"')
	{
		if (temp[sh->i] == '\'')
		{
			sh->i++;
			while (temp[sh->i] != '\'')
				sh->i++;
			sh->i++;
		}
		else
			sh->i++;
	}
	if (sh->i > start)
	{
		left = ft_substr(temp, start, sh->i - start);
		return (left);
	}	
	return (NULL);
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

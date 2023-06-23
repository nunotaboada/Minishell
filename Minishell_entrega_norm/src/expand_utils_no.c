/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:00:32 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/08 17:00:32 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

static char	*get_env1(char *var, t_shell *sh)
{
	int		pos;

	pos = pos_envp(var, sh->envp);
	if (pos < 0 || !ft_strchr(sh->envp[pos], '='))
		return (NULL);
	return (ft_strdup(sh->envp[pos] + (ft_strlen(var) + 1)));
}

static char	*ft_result(char *str, char *env)
{
	char	*result;

	result = NULL;
	printf("env dentro do ft_result: %s\n", env);
	printf("rest dentro do ft_result: %s\n", str);
	if (str && env)
		result = ft_strjoin(str, env);
	else if (str)
		result = ft_strdup(str);
	else if (env)
		result = ft_strdup(env);
	printf("result dentro do ft_result: %s\n", result);
	return (result);
}

static char	*checkenv(char *str, t_shell *sh)
{
	int			i;
	int			start;
	char		*rest;
	char		*var;
	char		*env;
	char		*word;

	if (!str)
		return (NULL);
	i = 0;
	rest = NULL;
	var = NULL;
	env = NULL;
	word = NULL;
	while (str[i] != '\0')
	{
		start = i;
		env = NULL;
		rest = NULL;
		while (str[i] != '$' && str[i])
			i++;
		if (i - start > 0)
		{
			rest = ft_substr(str, start, i - start);
			printf("rest com quotes checkEnv: %s\n", rest);
		}
		if (str[i] == '$')
		{
			i++;
			start = i;
			while (str[i] != '$' && str[i] && str[i] != '\'')
				i++;
			var = ft_substr(str, start, i - start);
			printf("var quotes checkEnv: %s\n", var);
			env = get_env1(var, sh);
			printf("env1 quotes checkEnv: %s\n", env);
			free (var);
		}
		word = concate(word, ft_result(rest, env));
		free(env);
		free(rest);
	}
	return (word);
}

char	*restexp(t_shell *sh, char *temp)
{
	int			start;
	char		*rest;
	char		*rest1;

	rest = NULL;
	rest1 = NULL;
	start = sh->i;
	while (temp[sh->i] != '\0' && temp[sh->i] != '$' && temp[sh->i] != '\"')
	{
		if (temp[sh->i] == '\'')
		{
			sh->i++;
			while (temp[sh->i] != '\'' && temp[sh->i] != '\0')
				sh->i++;
			sh->i++; // posso que ter de colocar um if par o caso null terminator
		}
		else
			sh->i++;
	}
	if (sh->i - start > 0)
	{
		printf("char start restExp:%c\n", temp[start]);
		printf("char final restExp:%c\n", temp[sh->i - 1]);
		printf("quotes final restExp:%d\n", sh->dquotes);
		if (sh->dquotes)
		{
			rest1 = ft_substr(temp, start, sh->i - start);
			printf("teste1\n");
			rest = checkenv(rest1, sh);
			printf("env quotes restExp: %s\n", rest);
			free(rest1);
		}
		else
		{
			rest = ft_substr(temp, start, sh->i - start - 2);
			printf("teste2 restExp\n");
		}
		return (rest);
	}
	else
		return (NULL);
}

char	*doexp(t_shell *sh, char *temp)
{
	int			start;
	char		*var;
	char		*env;

	var = NULL;
	env = NULL;
	start = 0;
	printf("char doExp %c\n", temp[sh->i]);
	if (temp[sh->i] == '\"')
	{
		sh->i++;
		sh->dquotes = 1;
	}
	if (temp[sh->i] == '$')
	{
		start = sh->i;
		sh->i++;
		while (temp[sh->i] != ' ' && temp[sh->i] != '$' && \
		temp[sh->i] != '\"' && temp[sh->i] != '\0' && temp[sh->i] != '\'')
			sh->i++;
		if (sh->i - start > 0)
		{
			var = ft_substr(temp, start, sh->i - start);
			printf("var1 doExp %s\n", var);
		}
		if (ft_strcmp(var, "$?") == 0)
		{
			free(var);
			return (ft_itoa(g_ex_status));
		}
		if ((ft_strcmp(var, "$") == 0))
			return (var);
		else
		{
			free(var);
			var = ft_substr(temp, start + 1, sh->i - start - 1);
			printf("var2 doExp 1: %s\n", var);
		}
		env = get_env(var, sh);
		printf("env doExp %s\n", env);
		if (env)
			return (ft_strdup(env));
	}
	return (NULL);
}

char	*allword(t_shell *sh, char *temp)
{
	char	*rest;
	char	*wordexp;
	char	*totalword;

	rest = NULL;
	totalword = NULL;
	wordexp = NULL;
	rest = restexp(sh, temp);
	printf("rest allWord %s\n", rest);
	printf("teste allWord %d\n", sh->i);
	wordexp = doexp(sh, temp);
	if (rest && wordexp)
	{
		totalword = ft_strjoin(rest, wordexp);
		free(rest);
		free(wordexp);
	}
	else if (rest)
	{
		totalword = ft_strdup(rest);
		free(rest);
	}
	else if (wordexp)
	{
		totalword = ft_strdup(wordexp);
		free(wordexp);
	}
	return (totalword);
}

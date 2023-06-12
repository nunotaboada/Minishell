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

extern int g_ex_status;

static char *ft_result(char *str, char *env)
{
	char *result;

	result = NULL;
	if (str && env)
	{
		result = ft_strjoin(str, env);
		// free(str);
		// free(env);
		// env = NULL;
	}
	else if (str)
	{
		result = ft_strdup(str);
		// free(str);
	}
	else if (env)
	{
		result = ft_strdup(env);
		// free(env);
		// env = NULL;
	}
	return (result);
}

static char *checkEnv(char *str, t_shell *sh)
{
	int i;
	int start;
	char *rest;
	char *var;
	char *env;
	char *word;

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
		while(str[i] != '$' && str[i])
			i++;
		if (i - start > 0)
		{
			rest = ft_substr(str, start , i - start);
			printf("rest com quotes checkEnv: %s\n", rest);
		}
		if (str[i] == '$')
		{
			i++;
			start = i;
			while(str[i] != '$' && str[i] && str[i] != '\'')
				i++;
			var = ft_substr(str, start, i - start);
			printf("var quotes checkEnv: %s\n", var);
			env = get_env(var, sh->envp);
			printf("env1 quotes checkEnv: %s\n", env);
			free (var);
		}
		word = concate(word, ft_result(rest, env));
		env = NULL;
		free(rest);
	}
	return (word);
}

char *restexp(t_shell *sh, char *temp)
{
		int start;
		char *rest;
		char *rest1;

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
				sh->i++;
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
				rest1 = ft_substr(temp, start , sh->i - start);
				printf("teste1\n");
				rest = checkEnv(rest1, sh);
				printf("env quotes restExp: %s\n", rest);
				free(rest1);
				// sh->dquotes = 0;
			}
			else
			{
				rest = ft_substr(temp, start, sh->i - start);
				printf("teste2 restExp\n");
			}
			return (rest);
		}
		else
			return (NULL);
}

// static char *ft_word2(t_shell *sh, char *temp, int start)
// {
// 	int pos;
// 	int i;
// 	char *var;

// 	i = 0;
// 	pos = start;
// 	var = ft_substr(temp, pos, sh->i - pos);
// 	printf("var word 2: %s\n", var);
// 	while (var[i])
// 	{

// 	}

// 	return (NULL);
// }

char *doExp(t_shell *sh, char *temp)
{
	int start;
	char *var;
	char *env;

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
		while (temp[sh->i] != ' ' && temp[sh->i] != '$' && temp[sh->i] != '\"' && temp[sh->i] != '\0' && temp[sh->i] != '\'') 
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
		env = get_env(var, sh->envp);
		printf("env doExp %s\n", env);
		if (env)
			return (ft_strdup(env)); 	
	}
	// else 
	// 	ft_word2(sh, temp, start);
	return (NULL);
}

char *allWord(t_shell *sh, char *temp)
{
	char *rest;
	char *wordExp;
	char *totalWord;

	rest = NULL;
	totalWord = NULL;
	wordExp = NULL;
	rest = restexp(sh, temp);
	printf("rest allWord %s\n", rest);
	printf("teste allWord %d\n", sh->i);
	wordExp = doExp(sh, temp);
	if (rest && wordExp)
	{
		totalWord = ft_strjoin(rest, wordExp);
		free(rest);
		free(wordExp);
	}
	else if (rest)
	{
		totalWord = ft_strdup(rest);
		free(rest);
	}
	else if (wordExp)
	{
		totalWord = ft_strdup(wordExp);
		free(wordExp);
	}
	return (totalWord);
}

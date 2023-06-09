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

char *restexp(t_shell *sh, char *temp)
{
		int start;
		char *rest;

		rest = NULL;
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
			rest = ft_substr(temp, start, sh->i - start);
			return (rest);
		}
		else
			return (NULL);
}

char *doExp(t_shell *sh, char *temp)
{
	int start;
	char *var;
	char *env;

	var = NULL;
	env = NULL;
	printf("char %c\n", temp[sh->i]);
	if (temp[sh->i] == '\"')
			sh->i++;
	if (temp[sh->i] == '$')
	{
		start = sh->i;
		sh->i++;
		while (temp[sh->i] != ' ' && temp[sh->i] != '$' && temp[sh->i] != '\"' && temp[sh->i] != '\0' && temp[sh->i] != '\'') 
			sh->i++;
		if (sh->i - start > 0)
		{
			var = ft_substr(temp, start + 1, sh->i - start - 1);
			printf("var %s\n", var);
		}
		if (ft_strcmp(var, "$?") == 0)
		{
			free(var);
			return (ft_itoa(g_ex_status));
		}
		if ((ft_strcmp(var, "$") == 0))
			return (var);
		env = get_env(var, sh->envp);
		printf("env %s\n", env);
		if (env)
			return (ft_strdup(env)); 	
	}
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
	printf("rest %s\n", rest);
	printf("teste %d\n", sh->i);
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

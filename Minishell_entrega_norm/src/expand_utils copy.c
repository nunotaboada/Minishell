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
	int len;

	len = ft_strlen(s);
	while (pos < len)
	{
		if (s[pos] == '$' || s[pos] == '\'' || s[pos] == '\"' || s[pos - 1] == '?' \
		|| s[pos] == '\0')
			return (pos);
		pos++;
	}
	return (len);
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
	if (!result)
		return (NULL);
	else
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
		if (str[i] == '$' && str[i + 1] == '\0')
		{
			word = concate(word, "$");
			return (word);
		}
		if (str[i] == '$')
		{
			i++;
			start = i;
			while (str[i] != '$' && str[i] && str[i] != '\'')
				i++;
			var = ft_substr(str, start, i - start);
			printf("var quotes checkEnv: %s\n", var);
			if (sh->dquotes)
				env = get_env(var, sh);
			else
				env = ft_substr(str, start - 1, i - start + 1);
			printf("env1 quotes checkEnv: %s\n", env);
			free (var);
		}
		printf("word quotes checkEnv: %s\n", word);
		word = concate(word, ft_result(rest, env));
		printf("word1 quotes checkEnv: %s\n", word);
		free(env);
		free(rest);
	}
	return (word);
}

/* devolve expansao ou null */
char	*doexp(t_shell *sh, char *temp)
{
	char	*expansion;
	char	*env;
	char	*rest1;
	int		i;
	int		start;

	// i = sh->i;
	i = 0;
	expansion = NULL;
	env = NULL;
	rest1 = NULL;
	printf("char inicio doexp %c\n", temp[sh->i]);
	if (temp[sh->i] == '\"')
	{
		sh->i++;
		printf(" before sh->dquotes %d\n", sh->dquotes);
		sh->dquotes = !sh->dquotes;
		printf(" after sh->dquotes %d\n", sh->dquotes);
		start = sh->i;
		while (temp[sh->i] != '\"' && temp[sh->i] !='\0')
			sh->i++;
		if (sh->i > start)
			rest1 = ft_substr(temp, start, sh->i - start);
		printf("rest1 dquotes %s\n", rest1);
		// if (sh->dquotes && temp[sh->i] != '\"')
			env = checkenv(rest1, sh);
		printf("left1 dquotes %s\n", env);
		printf("char fim dquotes 1 %c\n", temp[sh->i]);
		// posso ter de retirar é um teste para quando chegamos à quote que fecha
		if (temp[sh->i] == '\"')
		{
			sh->dquotes = !sh->dquotes; // tem de se fazer esta operação
			sh->i++;
		}
		printf("sh->i 2 %d\n", sh->i);
		printf("char fim dquotes 2 %c\n", temp[sh->i]);
		if (env)
			return (env);
		return (NULL);
	}
	i = sh->i;
	printf("char teste dquotes 1 %c\n", temp[sh->i]);
	printf(" incremento i %d\n", i);
	printf("end var pos %d\n", end_varpos(temp, i + 1));
	printf("end var pos char %c\n", temp[end_varpos(temp, i + 1)]);
	// if (end_varpos(temp, i + 1) = '$') // pode não funcionar
	if (end_varpos(temp, i + 1) < (int)ft_strlen(temp)) // tinha <= mas tive que colocar < devido ao caso 12345'$USER' que dava segfault
	{
		expansion = ft_substr(temp, i, end_varpos(temp, i + 1) - i);
		printf("expansion 1 %s\n", expansion);
	}
	// else
	// {
	// 	expansion = ft_substr(temp, i, end_varpos(temp, i + 1) - 1);
	// 	printf("expansion 2 %s\n", expansion);
	// }
	else
	{
		expansion = ft_substr(temp, i, end_varpos(temp, i + 1) - i);
		printf("expansion 2 %s\n", expansion);
	}
	if (ft_strcmp(expansion, "$?") == 0)
	{
		free(expansion);
		sh->i += 2;
		return (ft_itoa(g_ex_status));
	}
	// sh->i = end_varpos(temp, i + 1) - 1;
	printf("sh->i 4 %d\n", sh->i);
	if (!(ft_strcmp(expansion, "$")))
	{
		sh->i++;
		return (expansion);
	}
	if (ft_strlen(expansion))
		env = get_env(expansion + 1, sh);
	printf("len expansion 3 %ld\n", ft_strlen(expansion));
	printf("expansion 3 %s\n", expansion + 1);
	printf("env %s\n", env);
	free(expansion);
	if (env)
	{
		sh->i = end_varpos(temp, i + 1);
		return (env);
	}
	// sh->i++;
	sh->i = end_varpos(temp, i + 1);
	return (NULL);
}

char	*restexp(t_shell *sh, char *temp)
{
	char	*left;
	int		start;

	left = NULL;
	start = sh->i;
	printf("char antes dquotes %c\n", temp[sh->i]);
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
		printf("left dquotes %s\n", left);
		printf("char fim dquotes %c\n", temp[sh->i]);
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

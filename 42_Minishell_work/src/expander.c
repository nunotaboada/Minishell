/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:55:16 by nmoreira          #+#    #+#             */
/*   Updated: 2023/05/24 00:55:16 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_ex_status;

/* caso importante $USER$USERls-l$USER$USER e $USERls-l*/

static int is_alpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return (1);
    return (0);
}

static int check_trace(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!is_alpha(str[i]))
			return (i);
		i++;
	}
	return (0);
}

static int checkBarraInv(char *str)
{
	int i = 0;
	int barraInv = 0;

	if (!str) // verifica se não existe nada, útil quando não temos var com $
		return (0);
	while (str[i])
	{
		if (str[i] == '\\')
			barraInv = 1;
		i++;
	}
	return (barraInv);
}

static int posBarraInv(char *str)
{
	int i = 0;
	int pos = 0;

	while (str[i])
	{
		if (str[i] == '\\')
			pos++;
		i++;
	}
	return (pos);
}

/*utilizado para retirar a \ quando não existe pelicas, é feito com malloc para se puder fazer o free da string final em qualquer dos casos*/

static char *rmvBarraInv(char *str)
{
	int i = 0;
	int j = 0;
	int pos = 0;
	int len = 0;
	char *str1;

	str1 = NULL;
	pos = posBarraInv(str);
	str1 = (char*)malloc(sizeof(char) * (ft_strlen(str) - pos + 1));
	len = ft_strlen(str); // porque vou retirar um char
	while (str[i] && i < len)
	{
		if (str[i] != '\\')
		{
			str1[j] = str[i];
			j++;
		}
		i++;
	}
	str1[j] = '\0';
	return (str1);
}

static char *new_word(t_shell *sh, char *temp)
{
	char *left;
	char *left1;
	char *var;
	char *var1;
	char *env;
	char *env1;
	char *rest;
	char *new_str;
	char *new_str1;
	char *new_str2;
	int start;
	int trace;
	int pelicas;

	sh->i = 0;
	start = 0;
	trace = 0;
	pelicas = 0;
	var = NULL;
	var1 = NULL;
	env = NULL;
	env1 = NULL;
	rest = NULL;
	left = NULL;
	left1 = NULL;
	new_str = NULL;
	new_str1 = NULL;
	new_str2 = NULL;
	// printf("1 %c\n", temp[sh->i]);
	while (temp[sh->i] != '\0')
	{
		start = sh->i;
		printf("1 start %d 2 i %d\n", start, sh->i);
		while (temp[sh->i] != '\0' && temp[sh->i] != '$' && temp[sh->i] != '\"') // deteta o inicio sem $, também foi colocado o caso em temos \ no inicio
		{
			if (temp[sh->i] == '\'' || temp[0] == '\\') // este ciclo deve estar errado se existir algo do lado esq da.
			{
				pelicas = 1;
				sh->i++;
				start = sh->i;
				while (temp[sh->i] != '\'' && temp[sh->i] != '\0')
					sh->i++;
				if (sh->i - start > 0)
					left1 = ft_substr(temp, start, sh->i - start);
				printf("left1 %s\n", left1);
				sh->i++;// para não fazer duplo ciclo
			}
			else
				sh->i++;
		}
		if (left1)
		{
			left = ft_strdup(left1);
			free(left1);
			left1 = NULL;
		}
		else if (sh->i - start > 0)
		{
			left = ft_substr(temp, start, sh->i - start);
		}
		else
			left = NULL;
		printf("left %s\n", left);
		if (temp[sh->i] == '\"')
			sh->i++;
		if (temp[sh->i] == '$')
		{
			start = sh->i;
			sh->i++;
			while (temp[sh->i] != ' ' && temp[sh->i] != '$' && temp[sh->i] != '\"' && temp[sh->i] != '\0' && temp[sh->i] != '\'')
				sh->i++;
			if (sh->i - start > 0) // colocado para verificar o caso que vem a seguir
			{
				var = ft_substr(temp, start, sh->i - start);
				printf("var %s\n", var);
			}
			if (ft_strcmp(var, "$?") == 0)
			{
				env = ft_itoa(g_ex_status);
				new_str1 = ft_strdup(env);
				free(var);
				free(env);
				break;
			}
			else
			{
				free(var);
				var = ft_substr(temp, start + 1, sh->i - start - 1); // retira o $
				printf("var 2 %s\n", var);
				trace = check_trace(var);
				printf("var trace %c\n", var[trace]);
				printf("trace %d\n", trace);
				if (trace)
				{
					var1 = ft_substr(var, 0, trace);
					printf("var1 %s\n", var1);
					env1 = get_env(var1, sh->envp);
					printf("var1 %s\n", env1);
					printf("len var %ld\n", ft_strlen(var));
					if (var[trace] == '\\')
						rest = ft_substr(var, trace + 1, ft_strlen(var) - trace - 1);
					else
						rest = ft_substr(var, trace, ft_strlen(var) - trace);
					printf("rest %s\n", rest);
					env = ft_strjoin(env1, rest);
					// free(env1);
					free(rest);
					free(var1);
					// env = ft_substr(var, trace, ft_strlen(var) - trace);
				}
				else
					env = get_env(var, sh->envp); // env não é malloc
				free(var);
				printf("env %s\n", env);
			}
			
		}
		if (left && env)
		{
			new_str = ft_strjoin(left, env);
			free(left);
			env = NULL;
			// free(env);
		}
		else if (left)
		{
			new_str = ft_strdup(left);
			printf("new_str 2 %s\n", new_str);
			free(left);
		}
		else if (env)
		{
			new_str = ft_strdup(env);
			env = NULL;
			// free(env);
		}
		else 
		 	new_str = NULL;
		if (new_str1)
		{
			new_str1 = ft_strjoin(new_str1, new_str);
			// new_str = NULL;
		}
		else if (new_str) // paravo primeiro caso
		{
			new_str1 = ft_strdup(new_str);
			// new_str = NULL;
		}
		// else
		// free(var);
		if (new_str)
		{
			free(new_str);
			new_str = NULL;
		}
	}
	printf("new_str 3 %s\n", new_str1);
	if (checkBarraInv(new_str1) && !pelicas)
	{	
		new_str2 = rmvBarraInv(new_str1);
		free (new_str1);
		return (new_str2);
	}
	else
		return (new_str1);
}


int expand(t_shell *sh)
{
	char *temp;
	t_token *node;

	node = NULL;
	node = sh->head_token;
	while (node)
	{
		if (ft_strchr(node->word, '$'))
		{
			temp = ft_strdup(node->word);
			free(node->word);
			node->word = new_word(sh, temp);
			free(temp);
		}
		node = node->next;
	}
	printf("after expander\n");
	print_list(sh);
	return (0);
}
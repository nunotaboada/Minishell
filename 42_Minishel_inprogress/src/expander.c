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

char *concate(char *new_str, char *rest)
{
	char	*tmp;

	tmp = NULL;
	if (new_str)
	{
		tmp = ft_strdup(new_str);
		free(new_str);
		new_str = ft_strjoin(tmp, rest);
		free(tmp);
	}
	else
		new_str = ft_strdup(rest);
	return (new_str);
}

char *new_word(t_shell *sh, char *temp)
{
	char *rest;
	char *new_str;

	sh->i = 0;
	rest = NULL;
	new_str = NULL;
	// printf("1 %c\n", temp[sh->i]);
	while (temp[sh->i] != '\0')
	{
		rest = allWord(sh, temp);
		printf("rest1 %s\n", rest);
		if (rest)
		{
			new_str = concate(new_str, rest);
			free(rest);
			printf("%d\n", sh->i);
			// sh->i++; // verificar
		}
	}
	return (new_str);
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
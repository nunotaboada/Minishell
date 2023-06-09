/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aspas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:24:58 by nmoreira          #+#    #+#             */
/*   Updated: 2023/05/18 18:24:58 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int checkdAspas(t_shell *sh)
{
	int i;
	bool dentroDeAspas = false;
	bool dentroDeSAspas = false;

	i = 0;
	while (sh->cmd_line[i] !='\0')
	{
        if (sh->cmd_line[i] == '\"')
		    	dentroDeAspas = !dentroDeAspas;
        if (sh->cmd_line[i] == '\'')
		    	dentroDeSAspas = !dentroDeSAspas;
        i++;
    }
	if (dentroDeAspas)
	{
		error_quotes('\"');
		return (1);
	}
	if (dentroDeSAspas)
	{
		error_quotes('\'');
		return (1);
	}	
	return (0);
}

int countAspas(char *str)
{
	int i;
	int aspas;

	i = 0;
	aspas = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			aspas++;
		i++;
	}
	return (aspas);
}

void	wordOutAspas(t_token *node)
{
	char	c;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * ((ft_strlen(node->word) - (countAspas(node->word)) + 1)));
	while (node->word[i] != '\0')
	{
		if (node->word[i] == '\'' || node->word[i] == '\"')
		{
			c = node->word[i];
			i++;
			while (node->word[i] != c)
				str[j++] = node->word[i++];
			i++;
		}
		else
			str[j++] = node->word[i++];
	}
	free(node->word);
	str[j] = '\0';
	node->word = str;
}

int rmvAspas(t_shell *sh)
{
	t_token *node;

	node = NULL;
	node = sh->head_token;
	while (node)
	{
		if (!ft_strchr(node->word, '$'))
			wordOutAspas(node);
		node = node->next;
	}
	return (0);
}

int is_operator(char c)
{
	{
	if (c == 60)
		return (1);
	if (c == 62)
		return (1);
	if (c == 124)
		return (1);
	return (0);
	}
}
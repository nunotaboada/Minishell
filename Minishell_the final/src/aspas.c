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

extern int	g_ex_status;

/*alteração no while mais interno coloquei a detecção str[i] != '\0'*/
int	countaspas(char *str)
{
	char	c;
	int		i;
	int		pairs;

	i = 0;
	pairs = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			c = str[i];
			printf("c no par %c\n", str[i]);
			i++;
			pairs++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		i++;
	}
	printf("par %d\n", pairs);
	return (pairs);
}

void	wordoutaspas(t_token *node)
{
	char	c;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * ((ft_strlen(node->word) \
	- (countaspas(node->word) * 2) + 1)));
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

/*alteração no if dentro while devido ao heredoc*/
int	rmvaspas(t_shell *sh)
{
	t_token	*node;

	node = NULL;
	node = sh->head_token;
	while (node)
	{
		if ((node->prev) && ft_strcmp(node->prev->word, "<<"))
			return (0);
		else if (!ft_strchr(node->word, '$'))
			wordoutaspas(node);
		// else if (!((node->prev) && ft_strcmp(node->prev->word, "<<")))
		// 	wordoutaspas(node);
		node = node->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:48:59 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/20 14:48:59 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*concate(char *new_str, char *rest)
// {
// 	char	*tmp;

// 	tmp = NULL;
// 	if (new_str)
// 	{
// 		if (rest) // para funcionar no caso de "$USER$U e outros parecidos"
// 		{
// 			tmp = ft_strdup(new_str);
// 			free(new_str);
// 			new_str = ft_strjoin(tmp, rest);
// 			free(tmp);
// 		}
// 		else
// 			return (new_str);
// 	}
// 	else
// 		new_str = ft_strdup(rest);
// 	// free(rest); // ver se funciona com isto
// 	printf("new str com quotes checkEnv: %s\n", new_str);
// 	return (new_str);
// }

char	*concate(char *new_str, char *rest)
{
	char	*tmp;

	tmp = NULL;
	if (new_str && rest)
	{
		tmp = ft_strdup(new_str);
		free(new_str);
		new_str = ft_strjoin(tmp, rest);
		free(tmp);
	}
	else if (new_str)
		return (new_str);
	else if (rest)
		new_str = ft_strdup(rest);
	// free(rest); // ver se funciona com isto
	printf("new str com quotes checkEnv: %s\n", new_str);
	return (new_str);
}

char	*new_word(t_shell *sh, char *temp)
{
	char	*rest;
	char	*new_str;

	new_str = NULL;
	rest = NULL;
	sh->i = 0;
	while (temp[sh->i])
	{
		rest = allword(sh, temp);
		if (rest)
			new_str = concate(new_str, rest);
		// sh->i = end_varpos(temp, sh->i + 1);
		// sh->i++;
		printf("sh->i 3 newword %d\n", sh->i);
	}
	return (new_str);
}

int	expand(t_shell *sh)
{
	t_token	*node;
	char	*tmp;

	node = NULL;
	node = sh->head_token;
	while (node != NULL)
	{
		if (ft_strchr(node->word, '$'))
		{
			tmp = ft_strdup(node->word);
			printf("len do temp no expand %ld\n", ft_strlen(node->word));
			free(node->word);
			node->word = new_word(sh, tmp);
			free(tmp);
		}
		node = node->next;
	}
	return (0);
}

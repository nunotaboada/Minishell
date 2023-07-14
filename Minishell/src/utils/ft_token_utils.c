/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 11:23:24 by nmoreira          #+#    #+#             */
/*   Updated: 2023/02/12 11:23:24 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	node_type(t_shell *sh, char c)
{
	t_token		*last;

	last = sh->head_token;
	while (last->next)
		last = last->next;
	last->type = c;
}

/*função de teste - imprime a lista - palavras e tipo*/
void	print_list(t_shell *sh)
{
	t_token	*current;

	current = sh->head_token;
	if (!sh->head_token)
		return ;
	while (current != NULL)
	{
		printf("Word:%s, Type: %c\n", current->word, current->type);
		current = current->next;
	}
}

void	*node(t_shell *sh, char *word)
{
	t_token		*new;
	t_token		*last;

	new = NULL;
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = ft_strdup(word);
	new->type = 'N';
	new->next = NULL;
	new->prev = NULL;
	if (sh->head_token == NULL)
		sh->head_token = new;
	else
	{
		last = sh->head_token;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
	return (NULL);
}

void	token_node(t_shell *sh, char c)
{
	char	*str;

	str = NULL;
	if (sh->i - sh->wd_lim)
	{
		str = ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim));
		node(sh, str);
		free(str);
	}
	sh->wd_lim = sh->i;
	if (c != 'N')
		node_type(sh, c);
}

void	free_listtoken(t_token *list)
{
	t_token		*current;

	if (!list)
		return ;
	current = list;
	while (list != NULL)
	{
		free(current->word);
		current = list->next;
		free(list);
		list = current;
	}
	list = NULL;
}

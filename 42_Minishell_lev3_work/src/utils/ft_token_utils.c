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

void node_type(t_shell *sh, char c)
{
	t_token *last;

	last = sh->head_token;
	while (last->next)
		last = last->next;
	last->type = c;
}

/*função de teste - imprime a lista - palavras e tipo*/
void	print_list(t_shell *sh)
{
    t_token *current = sh->head_token;

	if(!sh->head_token)
		return ;
    while (current != NULL) {
        printf("Word:%s, Type: %c\n", current->word, current->type);
        current = current->next;
    }
}


void	*node(t_shell *sh, char *word)
{
	t_token	*new;
	t_token *last;

	new = NULL;
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = word;
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

void token_node(t_shell *sh, char c)
{
	char *str;

	str = NULL;
	if (sh->i - sh->wd_lim)
	{
		str = ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim));
		node(sh, str);
	}
	sh->wd_lim = sh->i;
	if (c != 'N')
		node_type(sh, c);
}

void	*node_cmds(t_cmds **node)
{
	t_cmds	*new;
	t_cmds *last;

	new = NULL;
	new = (t_cmds *)malloc(sizeof(t_cmds));
	printf("dentro do parser node_cmd %p\n", new);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (*node == NULL)
		*node = new;
	else
	{
		last = *node;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
	return (NULL);
}

/*funções utilizadas no push swap para a double list*/

// void	insert_node_after(t_shell *sh, t_token *node)
// {
// 	t_token *last;

// 	if (!sh->head_token || !node)
// 		return ;
// 	last = sh->head_token;
// 	while (last->next != NULL)
// 		last = last->next;
// 	last->next = node;
// 	node->prev = last;
// }

// void	insert_node_before(t_node *list, t_node *node)
// {
// 	if (!list || !node)
// 		return ;
// 	node->prev = list->prev;
// 	node->next = list;
// 	if (node->prev)
// 		node->prev->next = node;
// 	if (node->next)
// 		node->next->prev = node;
// }

// void	free_node(t_node *node)
// {
// 	if (node->next)
// 		node->next->prev = node->prev;
// 	if (node->prev)
// 		node->prev->next = node->next;
// 	free(node);
// }

void	free_listtoken(t_token *list)
{
	t_token	*current;

	if (!list)
		return ;
	current = list;
	while (list != NULL)
	{
		free(current->word); /*aqui estou a libertar a ft_substr*/
		current = list->next;
		free(list);
		list = current;
	}
	list = NULL;
}

// void	free_listcmd(t_cmds *list)
// {
// 	t_cmds	*current;
// 	int i = 0;

// 	if (!list)
// 		return ;
// 	current = list;
// 	while (list != NULL)
// 	{
// 		i = 0;
// 		while (list->cmd_line[i])
// 		{
// 			free(list->cmd_line[i]);
// 			i++;
// 		}
// 		free(current->cmd_line); /*aqui estou a libertar a ft_substr*/
// 		current = list->next;
// 		free(list);
// 		list = current;
// 	}
// 	list = NULL;
// }

void free_listcmd(t_cmds *head)
{
	char **cmd_line;
	int i;
	t_cmds *next;

    while (head != NULL)
    {
        // Liberta o array cmd_line
        if (head->cmd_line != NULL)
        {
            cmd_line = head->cmd_line;
            i = 0;
            while (cmd_line[i] != NULL)
            {
                free(cmd_line[i]);
                i++;
            }
            free(cmd_line);
        }
        free(head->new_dir);
        free(head->path);
        free(head->var);
        free(head->value);
		head->index = 0;
		next = head->next;
        free(head);
        head = next;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 03:45:41 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/10 03:45:41 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initnodecmds(t_cmds *node)
{
	node->cmd_line = NULL;
	node->new_dir = NULL;
	node->path = NULL;
	node->value = NULL;
	node->var = NULL;
	node->oldpwd = NULL;
	node->pwd = NULL;
	node->index = 0;
	node->total = 0;
	node->infd = STDIN_FILENO;
	node->outfd = STDOUT_FILENO;
}

/*retirar esta função*/
void	print_cmds(t_shell *sh)
{
	int			i;
	t_cmds		*current;

	current = sh->cmds;
	if (!sh->cmds)
		return ;
	while (current)
	{
		i = 0;
		while (current->cmd_line[i])
		{
			printf("index%d Cmd%d :%s\n", \
			current->index, i, current->cmd_line[i]);
			i++;
		}
		current = current->next;
	}
	printf("nº of pipes %d\n", sh->pipeop);
}

void	fill_index(t_shell *sh)
{
	int			i;
	t_cmds		*head;

	i = 0;
	if (!sh->cmds)
		return ;
	head = sh->cmds;
	while (head)
	{
		head->index = i;
		i++;
		head = head->next;
	}
	sh->cmds->total = i + 1;
}

void	*node_cmds(t_cmds **node)
{
	t_cmds			*new;
	t_cmds			*last;

	new = NULL;
	new = (t_cmds *)malloc(sizeof(t_cmds));
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

void	free_listcmd(t_cmds *head)
{
	int			i;
	char		**cmd_line;
	t_cmds		*next;

	while (head != NULL)
	{
		if (head->cmd_line != NULL)
		{
			i = -1;
			cmd_line = head->cmd_line;
			while (cmd_line[++i] != NULL)
				free(cmd_line[i]);
			free(cmd_line);
		}
		free(head->new_dir);
		free(head->path);
		free(head->var);
		free(head->value);
		free(head->oldpwd);
		free(head->pwd);
		head->index = 0;
		next = head->next;
		free(head);
		head = next;
	}
}

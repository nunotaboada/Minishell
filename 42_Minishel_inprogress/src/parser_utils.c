/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 04:04:31 by nmoreira          #+#    #+#             */
/*   Updated: 2023/06/09 04:04:31 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*não necessária*/
void	print_cmds(t_shell *sh)
{
    t_cmds *current = sh->cmds;
	int i = 0;

	if(!sh->cmds)
		return ;
	while (current)
	{
		i = 0;
    	while (current->cmd_line[i]) 
		{
        	printf("index%d Cmd%d :%s\n", current->index, i, current->cmd_line[i]);
        	i++;
    	}
		current = current->next;
	}
	printf("nº of pipes %d\n", sh->pipeOp);
}

void initNodeCmds(t_cmds *node)
{
	node->cmd_line = NULL;
	node->new_dir = NULL;
	node->path = NULL;
	node->value = NULL;
	node->var = NULL;
	node->index = 0;
	node->total = 0;
	node->fork = 0;
	node->infd = STDIN_FILENO;
	node->outfd = STDOUT_FILENO;
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
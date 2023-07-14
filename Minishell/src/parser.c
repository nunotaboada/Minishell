/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:36:11 by nmoreira          #+#    #+#             */
/*   Updated: 2023/05/28 17:36:11 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkoperators(t_shell *sh, t_token *token, t_cmds *node)
{
	if (ft_strcmp(token->word, "|") == 0)
	{
		sh->pipeop++;
		node_cmds(&(sh->cmds));
		node = node->next;
		initnodecmds(node);
	}
	else if (ft_strcmp(token->word, "<<") == 0)
		return (parse_redirecs(sh, node, token));
	else
		return (parse_redirecs(sh, node, token));
	return (0);
}

static void	init_cmds(t_cmds *node, char *str)
{
	node->cmd_line = (char **)malloc(sizeof(char *) * 2);
	node->cmd_line[0] = ft_strdup(str);
	node->cmd_line[1] = NULL;
}

static void	add_cmd(t_cmds *node, char *str)
{
	int		i;
	int		count;
	char	**new_cmd;

	i = 0;
	count = 0;
	new_cmd = NULL;
	while (node->cmd_line[count])
		count++;
	new_cmd = (char **)malloc(sizeof(char *) * (count + 2));
	while (i < count)
	{
		new_cmd[i] = ft_strdup(node->cmd_line[i]);
		free(node->cmd_line[i]);
		i++;
	}
	new_cmd[count] = ft_strdup(str);
	new_cmd[count + 1] = NULL;
	free(node->cmd_line);
	node->cmd_line = mtr_dup(new_cmd);
	mtr_free(new_cmd);
}

void	createnewcmd(t_cmds *node, char *str)
{
	if (node->cmd_line == NULL)
		init_cmds(node, str);
	else
		add_cmd(node, str);
}

/*fill index colocado no input após parser*/
int	parser(t_shell *sh)
{
	t_token		*token;
	t_cmds		*node;

	node = NULL;
	token = NULL;
	token = sh->head_token;
	node_cmds(&(sh->cmds));
	node = sh->cmds;
	initnodecmds(node);
	while (token != NULL)
	{
		if (token->type == 'O')
		{
			if (checkoperators(sh, token, node))
				return (1);
			if (node->next)
				node = node->next;
			if (ft_strcmp(token->word, "|") != 0 && token->next)
				token = token->next;
		}
		else if (token->word != NULL)
			createnewcmd(node, token->word);
		token = token->next;
	}
	return (0);
}

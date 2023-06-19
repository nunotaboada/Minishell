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
		return (parse_redirecs(node, token));
	else
		return (parse_redirecs(node, token));
	return (0);
}

void	createnewcmd(t_cmds *node, char *str)
{
	int			count;
	int			i;
	char		**new_cmd;

	count = 0;
	i = 0;
	new_cmd = NULL;
	if (node->cmd_line == NULL)
	{
		node->cmd_line = (char **)malloc(sizeof(char *) * 2);
		node->cmd_line[0] = ft_strdup(str);
		printf("cmd-line 1 %s\n", node->cmd_line[0]);
		node->cmd_line[1] = NULL;
		return ;
	}
	while (node->cmd_line[count])
		count++;
	new_cmd = (char **)malloc(sizeof(char *) * (count + 2));
	while (i < count)
	{
		new_cmd[i] = ft_strdup(node->cmd_line[i]);
		printf("new_cmd %s\n", node->cmd_line[i]);
		free(node->cmd_line[i]);
		i++;
	}
	new_cmd[count] = ft_strdup(str);
	new_cmd[count + 1] = NULL;
	free(node->cmd_line);
	node->cmd_line = mtr_dup(new_cmd);
	printf("cmd-line %s\n", node->cmd_line[1]);
	mtr_free(new_cmd);
}

int	parser(t_shell *sh)
{
	t_token		*token;
	t_cmds		*node;

	printf("dentro do parser\n");
	print_list(sh);
	node = NULL;
	token = NULL;
	token = sh->head_token;
	node_cmds(&(sh->cmds));
	node = sh->cmds;
	initnodecmds(node);
	printf("teste 0\n");
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
	fill_index(sh);
	printf("pointer cmd_line3 %p\n", sh->cmds->cmd_line);
	return (0);
}

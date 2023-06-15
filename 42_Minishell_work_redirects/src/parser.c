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

// char **cmd_line;
// 	char *new_dir;
// 	char *path;
// 	int infd;
// 	int outfd;
// 	int fork; //flag que diz se o nó foi feito fork
// 	char	*var;
// 	char	*value;
// 	int	index; // index de cada cmd - processo a criar
// 	int	total; // total de processo a criar
// 	struct s_cmds *next;
// 	struct s_cmds *prev;

void initNodeCmds(t_cmds *node)
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
	node->fork = 0;
	node->infd = STDIN_FILENO;
	node->outfd = STDOUT_FILENO;
}

int checkOperators(t_shell *sh, t_token *token, t_cmds *node)
{
	if (ft_strcmp(token->word, "|") == 0)
	{
		sh->pipeOp++;
		node_cmds(&(sh->cmds));
		node = node->next;// utilizado para iniciar o nó a seguir
		initNodeCmds(node);
	}
	else if (ft_strcmp(token->word, "<<") == 0) // pode ser alterado
		return (parse_redirecs(sh, node, token));
	else
		return (parse_redirecs(sh, node, token));
	return (0);
}

void createNewCmd(t_cmds *node, char *str)
{
    int count = 0;
	int i = 0;
    char **new_cmd = NULL;

    if (node->cmd_line == NULL)
    {
        node->cmd_line = (char **)malloc(sizeof(char *) * 2); // 2 porque além da str coloquo NULL
        // if (!str)
		// 	node->cmd_line[0] = NULL;
		node->cmd_line[0] = ft_strdup(str);
		printf("cmd-line 1 %s\n", node->cmd_line[0]);
        node->cmd_line[1] = NULL;
        return;
    }
    while (node->cmd_line[count])
        count++;
    new_cmd = (char **)malloc(sizeof(char *) * (count + 2)); //mesma razão que acima
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
    node->cmd_line = mtr_dup(new_cmd); // temos que utilizar dup porque senão não copia
	// printf("pointer cmd_line1 %p\n", node->cmd_line);
	printf("cmd-line %s\n", node->cmd_line[1]);
	mtr_free(new_cmd);
}

/*Caso importante quando coloco $fhggj dá nulo o ponter. Ou seja quando a variavel de ambiente não existe, não faz estrutura cmds, caso importante é quando é o primeiro ou seja, é o unico comando colocado neste caso temos de verificar se não dá segfault colocando a verificação se existe*/

int parser(t_shell *sh)
{
	t_token *token;
	t_cmds *node;

	printf("dentro do parser\n");
	print_list(sh);
	node = NULL;
	token = NULL;
	token = sh->head_token;
	node_cmds(&(sh->cmds));
	node = sh->cmds;		
	initNodeCmds(node);
	printf("teste 0\n");
	while (token != NULL)
	{
		if (token->type == 'O')
		{
			if (checkOperators(sh, token, node)) // se existir um pipe colocámos mais um nó onde vamos colocar o seguinte cmd
				return (1);
			if (node->next)  // acrescentamos o nó e aqui verificamos se existe
				node = node->next; // temos que incrementar o nó para utilizara a seguir
			//aqui tem que ser feito os redirects
		}
		else if (token->word != NULL)
			createNewCmd(node, token->word);
		token = token->next;
	}
	fill_index(sh);
	printf("pointer cmd_line3 %p\n", sh->cmds->cmd_line);
	print_cmds(sh); // verificar em caso de segfault
	return (0);
}

/*Quando a word vinda do lexer e expnader, caso não exista var de ambiente a word no token será nula, neste caso o sh->cmds->cmd_line é nil - nulo usar isto no exec e prever segfalts*/
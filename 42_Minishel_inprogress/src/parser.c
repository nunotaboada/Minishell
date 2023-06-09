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

int checkOperators(t_shell *sh, t_token *token, t_cmds *node)
{
	if (!ft_strcmp(token->word, "|"))
	{
		sh->pipeOp++;
		node_cmds(&(sh->cmds));
		node = node->next;// utilizado para iniciar o nó a seguir
		initNodeCmds(node);
	} // a partir daqui considerar os redirecs
	return (0);
}

void fill_index(t_shell *sh)
{
	int  i = 0;
	t_cmds *head;

	if(!sh->cmds)
		return ;
	head = sh->cmds;
	while (head)
	{
		head->index = i;
		i++;
		head = head->next;
	}
	sh->cmds->total = i + 1; // porque estamos a considerar o zero no i
}

void createNewCmd(t_cmds *node, char *str)
{
    int count = 0;
	int i = 0;
    char **new_cmd = NULL;

    if (node->cmd_line == NULL)
    {
        node->cmd_line = (char **)malloc(sizeof(char *) * 2); // 2 porque além da str coloquo NULL
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
	// printf("string cmd_line3 %s\n", sh->cmds->cmd_line[0]); // se testarmos com $USER | $fghj o apontador para o cmd line é nulo de acordo com o initiNode
	print_cmds(sh); // com palavra null aqui dá segfault
	return (0);
}

/*Quando a wor vinda do lexer e expnader, caso não exista var de ambiente a word no token será nula, neste caso o sh->cmds->cmd_line é nil - nulo usar isto no exec e prever segfalts*/
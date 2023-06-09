/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:07:59 by nmoreira          #+#    #+#             */
/*   Updated: 2023/05/14 20:07:59 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_ex_status;

int is_operator(char c)
{
	{
	if (c == 60) 		// <
		return (1);
	if (c == 62)		// >
		return (1);
	if (c == 124) 		// |
		return (1);
	return (0);
	}
}

void lexer_op(t_shell *sh)  // resolver a situação ls | e ls >>
{
	token_node(sh, 'N');
	if (sh->cmd_line[sh->i] == 60 || sh->cmd_line[sh->i] == 62)
	{
		if (sh->cmd_line[sh->i + 1] && sh->cmd_line[sh->i] == sh->cmd_line[sh->i + 1])
			sh->i += 2;
		else
			sh->i++;
	}
	else
		sh->i++;
	token_node(sh, 'O');
}

void spaces(t_shell *sh)
{
	if (sh->i - sh->wd_lim)
		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
	while (sh->cmd_line[sh->i] == ' ')
		sh->i++;
	sh->wd_lim = sh->i;
}

static int checkdAspas(t_shell *sh)
{
	int i;
	bool dentroDeAspas = false;
	bool dentroDeSAspas = false;

	i = 0;
	while (sh->cmd_line[i] !='\0')
	{
        if (sh->cmd_line[i] == '\"')
		    	dentroDeAspas = !dentroDeAspas;
        if (sh->cmd_line[i] == '\'')
		    	dentroDeSAspas = !dentroDeSAspas;
        i++;
    }
	if (dentroDeAspas)
	{
		error_quotes('\"');
		return (1);
	}
	if (dentroDeSAspas)
	{
		error_quotes('\'');
		return (1);
	}	
	return (0);
}

int div_input(t_shell *sh)
{
	bool dentroDeAspas = false;
	bool dentroDeAspasS = false;

	sh->i = 0;
	sh->wd_lim = 0;
	sh->pipeOp = 0;
	// sh->proc = 0;
	// printf("teste1\n");
	while (sh->cmd_line[sh->i] != '\0')
	{
		if (sh->cmd_line[sh->i] == '\"')
			dentroDeAspas = !dentroDeAspas;
		if (sh->cmd_line[sh->i] == '\'')
			dentroDeAspasS = !dentroDeAspasS;
		if (sh->cmd_line[sh->i] == ' ' && !dentroDeAspas && !dentroDeAspasS)
		 	spaces(sh);
		else if (is_operator(sh->cmd_line[sh->i]))
			lexer_op(sh);
		else
			sh->i++;
	}
	if (sh->i - sh->wd_lim)
		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
	return (0);
}

static int countAspas(char *str)
{
	int i;
	int aspas;

	i = 0;
	aspas = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			aspas++;
		i++;
	}
	return (aspas);
}

static void	wordOutAspas(t_token *node)
{
	char	c;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * ((ft_strlen(node->word)
					- (countAspas(node->word)) + 1)));
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

static int rmvAspas(t_shell *sh)
{
	t_token *node;

	node = NULL;
	node = sh->head_token;
	while (node)
	{
		if (!ft_strchr(node->word, '$'))
			wordOutAspas(node);
		node = node->next;
	}
	return (0);
}

static int div_words(t_shell *sh)
{
	if (checkdAspas(sh))
		return (1);
	if (div_input(sh))
		return (1);
	printf("after div words\n");
	print_list(sh);
	rmvAspas(sh);
	return (0);
}

int words(t_shell *sh)
{
	if (div_words(sh))
	{
		g_ex_status = 2;
		return (1);
	}
	printf("after remove aspas\n");
	print_list(sh);
	if (operators(sh))
		return (1);
	if (expand(sh))
		return (1);
	if (parser(sh))
		return (1);
	return (0);
}
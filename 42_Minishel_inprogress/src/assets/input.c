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

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*dest;
// 	size_t	j;

// 	dest = (char *)malloc(len + 1);
// 	if (!s || !dest)
// 		return (0);
// 	j = 0;
// 	while (start < ft_strlen(s) && j < len)
// 		dest[j++] = s[start++];
// 	dest[j] = '\0';
// 	return (dest);
// }

// int check_quotes(t_shell *sh)
// {
// 	int i;

// 	i = sh->i;
// 	if (sh->cmd_line[i] == 34)
// 	{
// 		// printf("%s\n", sh->cmd_line);
// 		i++;
// 		while (sh->cmd_line[i] != 34)
// 		{
// 			// printf("1 - %d\n", sh->i);
// 			if (sh->cmd_line[i] == '\0')
// 				return (error_quotes('\"'));
// 			i++;
// 			// printf("2 - %d\n", sh->i);
// 		}
// 	}
// 	i = sh->i;
// 	if (sh->cmd_line[i] == 39)
// 	{
// 		i++;
// 		while (sh->cmd_line[i] != 39)
// 		{
// 			if (sh->cmd_line[i] == '\0')
// 				return (error_quotes('\''));
// 			i++;
// 		}
// 	}
// 	return (0);
// }

// #include <stdio.h>
// #include <stdbool.h>

// char* detectarAspas(const char* comando) {
//     // static char comandoExecutavel[100]; // Tamanho máximo do comando executável
//     int i = 0;
//     bool dentroDeAspas = false;

//     // Percorre a string de comando
//     while (*comando) {
//         // Se encontrar uma aspa dupla
//         if (*comando == '\"') {
//             dentroDeAspas = !dentroDeAspas; // Alterna o estado de dentro de aspas
//         } else {
//             // Se não estiver dentro de aspas, copia o caractere para o comando executável
//             if (!dentroDeAspas) {
//                 comandoExecutavel[i] = *comando;
//                 i++;
//             }
//         }
//         comando++;
//     }

//     comandoExecutavel[i] = '\0'; // Adiciona o caractere nulo ao final do comando executável

//     return comandoExecutavel;
// }

// static int detectarAspas(t_shell *sh) 
// {
// 	int i;
// 	int flag;
// 	char *str;
//     bool dentroDeAspas = false;

// 	i = 0;
// 	flag =0;
// 	str = sh->cmd_line;
//     // Percorre a string de comando
//     while (*sh->cmd_line) 
// 	{
//         // Se encontrar uma aspa dupla
//         if (*sh->cmd_line == '\"')
// 		    dentroDeAspas = !dentroDeAspas; // Alterna o estado de dentro de aspas
// 		if (dentroDeAspas)
// 		{
// 			i++;
// 			flag = 1;
// 		}
// 		if (!dentroDeAspas && flag)
// 		{
// 			sh->i += i;
// 			node(sh, ft_substr(str, sh->wd_lim, (sh->i - sh->wd_lim)));
// 			str = sh->cmd_line;
// 			sh->wd_lim = sh->i;
// 		}
//         sh->cmd_line++;
//     }
// 	sh->wd_lim = sh->i;
// 	if (dentroDeAspas) 
// 		return (error_quotes('\"'));
// 	return (0);
// }

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

// void lexer_op(t_shell *sh)
// {
// 	if (sh->i - sh->wd_lim)
// 		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim))); // se tivermos o operador junto das palavras sem espaços
// 	sh->wd_lim = sh->i;
// 	if (sh->cmd_line[sh->i] == 60 || sh->cmd_line[sh->i] == 62)
// 	{
// 		if (sh->cmd_line[sh->i + 1] && sh->cmd_line[sh->i] == sh->cmd_line[sh->i + 1])
// 			sh->i += 2;
// 		else
// 			sh->i++;
// 	}
// 	else
// 		sh->i++;
// 	if (sh->i - sh->wd_lim)
// 		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
// 	sh->wd_lim = sh->i;
// 	node_type(sh, 'O');
// }

void lexer_op(t_shell *sh)
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

void lexer_word(t_shell *sh)
{
	if (sh->i - sh->wd_lim)
		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
	// while (sh->cmd_line[sh->i] == ' ')
	// 	sh->i++;
	sh->wd_lim = sh->i;
	sh->i++;
}

int div_input(t_shell *sh)
{
	sh->i = 0;
	sh->wd_lim = 0;
	// printf("teste1\n");
	while (sh->cmd_line[sh->i] != '\0')
	{
		if (sh->cmd_line[sh->i] == '\'' || sh->cmd_line[sh->i] == '\"')
		{
			// printf("teste2\n");
			if (detectarAspas(sh))
			{
				// free_listtoken(sh->head_token); estou a libertar nas aspas
				return (1); // estava exit (1);
			}
			// printf("%d\n", sh->i);
		}
		else if (is_operator(sh->cmd_line[sh->i]))
			lexer_op(sh);
		else if (sh->cmd_line[sh->i] == ' ')
		 	lexer_word(sh);
		else
			sh->i++;
	}
	// printf("%d\n", sh->i);
	if (sh->i - sh->wd_lim)
		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
	return (0);
}

int words(t_shell *sh)
{
	if (div_input(sh))
	{
		g_ex_status = 2;
		return (1);
	}
	if (operators(sh))
		return (1);
	// if (expand(sh))
	// 	return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aspas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:24:58 by nmoreira          #+#    #+#             */
/*   Updated: 2023/05/18 18:24:58 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// int detectarAspas1(t_shell *sh) 
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

// int detectarAspas_ok(t_shell *sh) 
// {
//     bool dentroDeAspas = false;

// 	if (sh->i - sh->wd_lim)
// 		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
// 	sh->wd_lim = sh->i;
// 	dentroDeAspas = !dentroDeAspas;
// 	sh->i++;
//     while (dentroDeAspas && sh->cmd_line[sh->i] !='\0') 
// 	{
//         if (sh->cmd_line[sh->i] == '\"')
// 		    dentroDeAspas = !dentroDeAspas;
//         sh->i++;
//     }
// 	if (dentroDeAspas)
// 	{
// 		error_quotes('\"');
// 		// free_list(sh->head_token);
// 		return (1);
// 	}
// 	else
// 	{
// 		if (sh->i - sh->wd_lim)
// 			node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
// 		sh->wd_lim = sh->i;
// 	}
// 	return (0);
// }

// int detectarAspas(t_shell *sh) 
// {
//     bool dentroDeAspas = false;
//     bool dentroDeAspas_S = false;

// 	if (sh->i - sh->wd_lim)
// 		node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
// 	sh->wd_lim = sh->i;
// 	dentroDeAspas = !dentroDeAspas;
	
// 	if (sh->cmd_line[sh->i] == '\"')
// 	{
// 		sh->i++;
//     	while (dentroDeAspas && sh->cmd_line[sh->i] !='\0') 
// 		{
//         	if (sh->cmd_line[sh->i] == '\"')
// 		    	dentroDeAspas = !dentroDeAspas;
//         	sh->i++;
//     	}
// 		if (dentroDeAspas)
// 		{
// 			error_quotes('\"');
// 			// free_list(sh->head_token);
// 			return (1);
// 		}
// 		else
// 		{
// 			if (sh->i - sh->wd_lim)
// 				node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
// 			sh->wd_lim = sh->i;
// 		}
// 		return (0);
// 	}
// 	dentroDeAspas_S = !dentroDeAspas_S;
// 	if (sh->cmd_line[sh->i] == '\'')
// 	{
// 		sh->i++;
//     	while (dentroDeAspas_S && sh->cmd_line[sh->i] !='\0') 
// 		{
//         	if (sh->cmd_line[sh->i] == '\'')
// 		    	dentroDeAspas_S = !dentroDeAspas_S;
//         	sh->i++;
//     	}
// 		if (dentroDeAspas_S)
// 		{
// 			error_quotes('\'');
// 			// free_list(sh->head_token);
// 			return (1);
// 		}
// 		else
// 		{
// 			if (sh->i - sh->wd_lim)
// 				node(sh, ft_substr(sh->cmd_line, sh->wd_lim, (sh->i - sh->wd_lim)));
// 			sh->wd_lim = sh->i;
// 		}
// 		return (0);
// 	}
// 	return (0);
// }

// static int is_alpha(char c)
// {
//     if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '$')
//         return (1);
//     return (0);
// }

// static int check_char(t_shell *sh)
// {
// 	if (sh->i - 1 < 0)
// 		return (0);
// 	if (sh->i + 1 == '\0')
// 		return (0);
// 	if((sh->cmd_line[sh->i] == '\'' || sh->cmd_line[sh->i] == '\"') && is_alpha(sh->cmd_line[sh->i - 1]) && is_alpha(sh->cmd_line[sh->i + 1]))
// 		return (1);
// 	return (0);
// }

int detectarAspas(t_shell *sh)
{
    bool dentroDeAspas = false;
    bool dentroDeAspas_S = false;

	// if (check_char(sh))
	// {
	// 	while (sh->cmd_line[sh->i] && sh->cmd_line[sh->i] != ' ' && !dentroDeAspas)
	// 		sh->i++;
	// 	return (0);
	// }
	token_node(sh, 'N');
	dentroDeAspas = !dentroDeAspas;
	if (sh->cmd_line[sh->i] == '\"')
	{
		sh->i++;
    	while (dentroDeAspas && sh->cmd_line[sh->i] !='\0')
		{
        	if (sh->cmd_line[sh->i] == '\"')
		    	dentroDeAspas = !dentroDeAspas;
        	sh->i++;
    	}
		if (dentroDeAspas)
		{
			error_quotes('\"');
			// free_listtoken(sh->head_token); //ver se é necessário ou não
			return (1);
		}
		else
			token_node(sh, 'D');
		return (0);
	}
	dentroDeAspas_S = !dentroDeAspas_S;
	if (sh->cmd_line[sh->i] == '\'')
	{
		sh->i++;
    	while (dentroDeAspas_S && sh->cmd_line[sh->i] !='\0')
		{
        	if (sh->cmd_line[sh->i] == '\'')
		    	dentroDeAspas_S = !dentroDeAspas_S;
        	sh->i++;
    	}
		if (dentroDeAspas_S)
		{
			error_quotes('\'');
			// free_listtoken(sh->head_token); //ver se é necessário ou não
			return (1);
		}
		else
			token_node(sh, 'S');
		return (0);
	}
	return (0);
}
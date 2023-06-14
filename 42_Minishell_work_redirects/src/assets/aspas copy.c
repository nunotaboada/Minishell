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
		// return (0);
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
		// return (0);
	}
	return (0);
}


int checkdAspas(t_shell *sh)
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:03:22 by nmoreira          #+#    #+#             */
/*   Updated: 2023/05/16 16:03:22 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

int	error_quotes(char erro)
{
	if (erro == '\'')
		write(1, \
		"minishell: unexpected error while looking for matching quotes \'\n", 65);
	if (erro == '\"')
		write(1, \
		"minishell: unexpected error while looking for matching quotes \"\n", 65);
	return (0);
}

void	errorfork(char *str1, char *str2, char *str3, int code)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	g_ex_status = code;
}

void	errorminishell(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
}

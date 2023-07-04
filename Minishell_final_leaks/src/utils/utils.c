/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:55:12 by nsoares-          #+#    #+#             */
/*   Updated: 2023/05/17 10:22:35 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nb_of_args(t_cmds *cmds)
{
	int		i;

	i = 0;
	while (cmds->cmd_line[i] != NULL)
		i++;
	return (i);
}

int	pos_char(char *str, char c)
{
	int		i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	if (c == '\0')
		return (i);
	return (-1);
}

void	put_var_env_from_cmd(char *cmd, t_shell *shell)
{
	char	*var;
	char	*value;
	char	*equals;

	equals = ft_strchr(cmd, '=');
	if (equals)
	{
		var = ft_substr(cmd, 0, equals - cmd);
		value = ft_strdup(equals + 1);
	}
	else
	{
		var = ft_strdup(cmd);
		value = NULL;
	}
	put_var_env(var, value, shell);
	free(var);
	free(value);
}

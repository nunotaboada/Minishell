/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:09:38 by nmoreira          #+#    #+#             */
/*   Updated: 2023/05/17 13:26:05 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pos_envp(char *var, char **envp)
{
	int i;
	int len;

	if (!envp || !*envp)
		return (-1);
	len = ft_strlen(var);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, len))
		{
			if (pos_char(var, '=') == len || pos_char(var, '\0') == len)
				return (i);
		}
	}
	return (-1);
}

/*se não existir = o strchr devolve nulo - não valor da var envp*/
char *get_env(char *var, char **envp)
{
	int i;
	// int len;

	i = pos_envp(var, envp);
	// printf("pos env %d\n", i);
	if (i < 0 || !ft_strchr(envp[i], '='))
		return (NULL);
	// len = ft_strlen(var);
	// printf("len var env %d\n", len);
	// printf("len var env %s\n", ft_strchr(envp[i], '='));
	return (ft_strchr(envp[i], '=') + 1); // para compensar o igual
}

int put_var_env(char *var, char *value, t_shell *shell)
{
	int pos;

	pos = pos_envp(var, shell->envp);
	if (value == NULL)
	{
		if (pos < 0)
			shell->envp = mtr_addnew(var, shell->envp);
		return 0;
	}
	if (pos < 0)
		shell->envp = mtr_addnew(ft_strjoin(var, ft_strjoin("=", value)), shell->envp);
	else
	{
		free(shell->envp[pos]);
		shell->envp[pos] = ft_strjoin(var, ft_strjoin("=", value));
	}
	return (0);
}

void remv_var_env(char *var, t_shell *shell)
{
	int pos;

	pos = pos_envp(var, shell->envp);
	if (pos < 0)
		return ;
	shell->envp = mtr_rmv(pos, shell->envp);
}
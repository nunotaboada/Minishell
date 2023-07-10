/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:01:09 by nsoares-          #+#    #+#             */
/*   Updated: 2023/07/09 20:04:06 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	errorforkenv(char *str1, char *str2, char *str3, int code)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	return (g_ex_status = code);
}

int	built_env(t_shell *shell)
{
	int		i;

	i = 0;
	if (!shell->cmds->path)
		return (errorforkenv("minishell: ", \
		shell->cmds->cmd_line[0], ": No such file or directory\n", 127));
	if (!*shell->envp)
		return (g_ex_status = 0);
	while (shell->envp[i] && ft_strchr(shell->envp[i], '='))
		printf("%s\n", shell->envp[i++]);
	return (g_ex_status = 0);
}

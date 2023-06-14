/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:18:20 by nsoares-          #+#    #+#             */
/*   Updated: 2023/05/16 15:47:23 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int built_export(t_shell *shell ,t_cmds *cmds)
{
    int i;
    int j;

    i = 1;
    if (nb_of_args(cmds) == 1)
        while (shell->envp[i] && ft_strchr(shell->envp[i], '='))
            printf("declare -x %s\n", shell->envp[i++]);
    else if (nb_of_args(cmds) > 1)
    {
        while (i < nb_of_args(cmds))
        {
            j = pos_char(cmds->cmd_line[i], '=');
            if (j <= 0)
                return (1); // retornar erro escrito!
            cmds->var = ft_substr(cmds->cmd_line[i], 0, j);
			cmds->value = ft_strdup(cmds->cmd_line[i] + (j + 1));
			put_var_env(cmds, shell);
			free(cmds->var);
			free(cmds->value);
            i++;
        }
    }
    return (g_ex_status = 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:18:20 by nsoares-          #+#    #+#             */
/*   Updated: 2023/05/19 16:09:12 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int built_export(t_shell *shell ,t_cmds *cmds)
{
    char *var;
    char *value;
    int i;
    int j;

    i = 1;
    print_export(shell, cmds);
    if (nb_of_args(cmds) > 1)
    {
        while (i < nb_of_args(cmds))
        {
            if (valid_identifier(cmds->cmd_line[i]) == false)
                return (error_export(shell, cmds->cmd_line[i]));
            j = pos_char(cmds->cmd_line[i], '=');
            if (j <= 0)
                return (error_export(shell, cmds->cmd_line[i]));
            var = ft_substr(cmds->cmd_line[i], 0, j);
			value = ft_strdup(cmds->cmd_line[i] + (j + 1));
			put_var_env(var, value, shell);
			free(var);
			free(value);
            i++;
        }
    }
    return (g_ex_status = 0);
}

void print_export(t_shell *shell, t_cmds *cmds)
{
    int i;

    i = 0;
    if (nb_of_args(cmds) == 1)
        while (shell->envp[i] && ft_strchr(shell->envp[i], '='))
            printf("declare -x %s\n", shell->envp[i++]);
}

int error_export(t_shell *shell, char *var)
{
    if (!pos_char(var, '=') || valid_identifier(var) == false)
    {
        printf("minishell: ");
        printf("export: `%s", var);
        printf("': not a valid identifier\n");
        return (g_ex_status = 1);
    }
    put_var_env(var, NULL, shell);
    return (g_ex_status = 0);
}

bool valid_identifier(char *var) 
{
    int i;

    if (!isalpha(var[0]) && var[0] != '_')
        return false; // Não começa com uma letra
    i = 1;
    while (var[i]) 
    {
        if (!isalnum(var[i]) && var[i] != '_' && var[i] != '=') 
            return false; // Contém caracteres inválidos
        if (var[i] == '=')
            break;
        i++;
    }
    return true;
}


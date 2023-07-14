/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:18:20 by nsoares-          #+#    #+#             */
/*   Updated: 2023/07/05 15:22:28 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	valid_identifier(char *var)
{
	int	i;

	if (!isalpha(var[0]) && var[0] != '_')
		return (false);
	i = 1;
	while (var[i])
	{
		if (!isalnum(var[i]) && var[i] != '_' && var[i] != '=')
			return (false);
		if (var[i] == '=')
			break ;
		i++;
	}
	return (true);
}

static int	error_export(t_shell *shell, char *var)
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

/*foi libertado no fim a matriz env*/
static void	print_export(t_shell *shell)
{
	char	*env_value;
	char	**env;
	int		i;
	int		j;

	i = -1;
	env = mtr_dup(shell->envp);
	while (env[++i])
	{
		printf("declare -x ");
		env_value = ft_strchr(env[i], '=');
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			printf("%c", env[i][j++]);
		if (env_value)
		{
			printf("=");
			printf("\"%s\"", env_value + 1);
		}
		printf("\n");
	}
	mtr_free(env);
}

static int	put_var_and_values(t_cmds *cmds, t_shell *shell)
{
	int	i;

	i = 0;
	while (++i < nb_of_args(cmds))
	{
		if (valid_identifier(cmds->cmd_line[i]) == false)
			return (error_export(shell, cmds->cmd_line[i]));
		put_var_env_from_cmd(cmds->cmd_line[i], shell);
	}
	return (g_ex_status = 0);
}

int	built_export(t_shell *shell, t_cmds *cmds)
{
	if (nb_of_args(cmds) > 1)
		put_var_and_values(cmds, shell);
	else
		print_export(shell);
	return (g_ex_status = 0);
}

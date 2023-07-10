/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:24:09 by nsoares-          #+#    #+#             */
/*   Updated: 2023/06/27 21:16:52 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	args_numbers(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	built_exit(t_cmds *cmds)
{
	int	nb_args;
	int	exit_status;

	nb_args = nb_of_args(cmds);
	if (args_numbers(cmds->cmd_line[1]) == 1)
	{
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", cmds->cmd_line[1]);
		exit_status = 2;
		exit(g_ex_status = exit_status);
	}
	if (nb_args == 2 && args_numbers(cmds->cmd_line[1]) == 0)
		g_ex_status = ft_atoi(cmds->cmd_line[1]);
	printf("exit\n");
	if (nb_args > 2 && args_numbers(cmds->cmd_line[1]) == 0)
	{
		printf("bash: exit: too many arguments\n");
		exit_status = 1;
		return (g_ex_status = exit_status);
	}
	exit(g_ex_status);
}

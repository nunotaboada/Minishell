/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:31:20 by nsoares-          #+#    #+#             */
/*   Updated: 2023/07/12 13:20:14 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ex_status;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_ex_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, " \n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("Quit: (core dumped)\n");
		g_ex_status = 131;
		signal(SIGQUIT, SIG_DFL);
	}
}

void	signal_quit1(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_ex_status = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		signal(SIGQUIT, SIG_DFL);
	}
}

void	signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

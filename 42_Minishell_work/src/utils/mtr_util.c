/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtr_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:44:10 by nmoreira          #+#    #+#             */
/*   Updated: 2023/05/12 16:24:35 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int mtr_len(char **matriz)
{
	int i;

	i = 0;
	while (matriz && matriz[i])
		i++;
	return (i);
}

void mtr_free(char **matriz)
{
	int i;

	i = 0;
	if (!matriz)
		return ;
	while (matriz[i])
	{
		free (matriz[i]);
		i++;
	}
	free(matriz);
	matriz = NULL;
}

char **mtr_dup(char **matriz)
{
	char **dup;
	int i;

	i = 0;
	dup = (char **)malloc(sizeof(char *) * (mtr_len(matriz) + 1));
	if (!dup)
		return (NULL);
	while (matriz[i])
	{
		dup[i] = ft_strdup(matriz[i]);
		if (!dup[i])
		{
			mtr_free(dup);	
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

char **mtr_addnew(char *str, char **matrizold)
{
	char **matriznew;
	int len;
	int i;

	i = -1;
	len = mtr_len(matrizold) + 1;
	matriznew = (char **)malloc(sizeof(char *) * (len + 1));
	if (!matriznew)
		return (NULL);
	while (matrizold[++i])
	{
		matriznew[i] = ft_strdup(matrizold[i]);
		if (!matriznew[i])
		{
			mtr_free(matriznew);
			mtr_free(matrizold);
			return (NULL);
		}
	}
	matriznew[i] = ft_strdup(str);
	matriznew[i + 1] = NULL;
	if (!matriznew[i])
		mtr_free(matriznew);
	mtr_free(matrizold);
	return (matriznew);
}

char **mtr_rmv(int pos, char **matrizold)
{
	char **matriznew;
	int len;
	int i;

	i = -1;
	len = mtr_len(matrizold) - 1;
	matriznew = (char **)malloc(sizeof(char *) * (len + 1));
	if (!matriznew)
		return (NULL);
	while (matrizold[++i] && i < len)
	{
		if (i < pos)
			matriznew[i] = ft_strdup(matrizold[i]);
		else
			matriznew[i] = ft_strdup(matrizold[i + 1]);
		if (!matriznew[i])
		{
			mtr_free(matriznew);
			mtr_free(matrizold);
			return (NULL);
		}
	}
	matriznew[i] = NULL;
	mtr_free(matrizold);
	return (matriznew);
}

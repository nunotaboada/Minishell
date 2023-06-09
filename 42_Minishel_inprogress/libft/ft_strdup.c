/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:44:47 by nsoares-          #+#    #+#             */
/*   Updated: 2022/11/16 22:38:11 by nsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s, ft_strlen(s) + 1);
	return (dest);
}

/*int main()
{
    char *str = "test";
    char *result;
    result = ft_strdup(str);
    
    printf("The string: %s", result);
    return 0;
}*/
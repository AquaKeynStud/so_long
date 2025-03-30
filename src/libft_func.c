/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:01:35 by arocca            #+#    #+#             */
/*   Updated: 2025/03/30 18:10:05 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "so_long.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
		str[i++] = c;
	return (s);
}

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (little[j] && big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size || size > SIZE_MAX / nmemb)
		return (NULL);
	tab = malloc(size * nmemb);
	if (!tab)
		return (NULL);
	ft_memset(tab, 0, size * nmemb);
	return (tab);
}

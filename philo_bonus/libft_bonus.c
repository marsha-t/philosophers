/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:35:52 by mateo             #+#    #+#             */
/*   Updated: 2024/07/29 11:37:11 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_i_count(int x)
{
	int	count;

	count = 0;
	if (x < 1)
		count++;
	while (x)
	{
		count++;
		x /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	int			count;
	long long	x;

	x = n;
	count = ft_i_count(n);
	ptr = (char *)malloc(sizeof(char) * (count + 1));
	if (!ptr)
		return (0);
	ptr[count] = '\0';
	if (x < 0)
		x = -x;
	while (count--)
	{
		ptr[count] = (x % 10) + '0';
		x = x / 10;
	}
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	tot_len;
	int		i;

	if ((!s1) || (!s2))
		return (0);
	tot_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = (char *)malloc(sizeof(char) * tot_len);
	if (!ptr)
		return (0);
	i = 0;
	while (*s1)
		ptr[i++] = *(s1)++;
	while (*s2)
		ptr[i++] = *(s2)++;
	ptr[i] = '\0';
	return (ptr);
}

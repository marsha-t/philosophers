/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:19:10 by mateo             #+#    #+#             */
/*   Updated: 2024/07/24 10:32:11 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	only_digits check whether str is made up of only digits 
	- returns 0 if any char is non-digit
	- returns 1 otherwise */
int	only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

/* ft_atoi converts str into int 
	- doesn't cater for whitespace nor signs 
	- returns -1 if number greater than INT_MAX */
int	ft_atoi(const char *str)
{
	long long	r;
	int			s;

	s = 1;
	r = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	while ((*str >= '0') && (*str <= '9'))
	{
		r = r * 10 + (*str - '0') * s;
		str++;
	}
	if (r > INT_MAX)
		return (-1);
	return (r);
}

/* check_arg checks:
	- arguments made up of only digits
	- arg is not greater than INT_MAX
	- arg is not 0 for any of the arguments
		(incl no. of meals) 
	- returns 1 if args are OK */
int	check_arg(int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	while (i < argc)
	{
		if (!only_digits(argv[i]))
			return (0);
		num = ft_atoi(argv[i]);
		if (num <= 0)
			return (0);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:44:24 by mateo             #+#    #+#             */
/*   Updated: 2024/07/29 12:54:32 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	quick_check_dead returns value of philo->end_cycle
	(but does it locking and unlocking end_mutex) */
int	quick_check_dead(t_philo *philo)
{
	sem_wait(philo->end_sem);
	if (1 == *(philo->end_cycle))
	{
		sem_post(philo->end_sem);
		return (1);
	}
	sem_post(philo->end_sem);
	return (0);
}

/*	print_status prints the status of a given philo
	returns 1 if death occurred */
int	print_status(char *str, t_philo *philo)
{
	sem_wait(philo->print_sem);
	if (quick_check_dead(philo) != 1)
	{
		printf("%ld %d %s\n", time_now_ms() - philo->meta->start_time, \
			philo->id, str);
		sem_post(philo->print_sem);
		return (0);
	}
	sem_post(philo->print_sem);
	return (1);
}

/*	usleep_check 'sleeps' for ms MILIseconds
	- checks during sleep whether end conditions have been reached
	It accounts for time used for checking */
int	usleep_check(t_philo *philo, time_t ms)
{
	time_t	start;

	start = time_now_ms();
	while (time_now_ms() - start < ms)
	{
		if (1 == quick_check_dead(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

/*	time_now_ms	returns no. of MILIseconds since epoch*/
time_t	time_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

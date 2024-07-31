/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 06:28:41 by mateo             #+#    #+#             */
/*   Updated: 2024/07/31 14:13:10 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	unlock_forks unlocks forks (number as determined by i)*/
void	unlock_forks(int i, t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
	if (i == 2)
		pthread_mutex_unlock(philo->fork_r);
}

/*	eating
	- order: 
		- picks up forks
		- prints status
		- update last_meal and eating
		- pauses philo for time_eat
		- releases forks
		- update num_meals and eating
	- returns 1 if end_cycle is 1 (via quick_check_dead)
		when printing status or eating
*/
int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	if (print_status(YELLOW "has taken a fork" RESET, philo, 0) == 1)
		return (unlock_forks(1, philo), 1);
	pthread_mutex_lock(philo->fork_r);
	if (print_status(YELLOW "has taken a fork" RESET, philo, 0) == 1)
		return (unlock_forks(2, philo), 1);
	if (print_status(GREEN "is eating" RESET, philo, 0) == 1)
		return (unlock_forks(2, philo), 1);
	pthread_mutex_lock(philo->last_meal_mutex);
	philo->last_meal = time_now_ms();
	philo->eating = 1;
	pthread_mutex_unlock(philo->last_meal_mutex);
	if (1 == usleep_check(philo, philo->meta->time_eat))
		return (unlock_forks(2, philo), 1);
	unlock_forks(2, philo);
	pthread_mutex_lock(philo->num_meals_mutex);
	philo->num_meals++;
	pthread_mutex_unlock(philo->num_meals_mutex);
	pthread_mutex_lock(philo->last_meal_mutex);
	philo->eating = 0;
	pthread_mutex_unlock(philo->last_meal_mutex);
	return (0);
}

/*	sleeping 
	- order
		- prints status 
		- pauses philo for time_sleep
	- returns 1 if end_cycle is 1 (via quick_check_dead)
		when printing status or sleeping */
int	sleeping(t_philo *philo)
{
	if (print_status(BLUE "is sleeping" RESET, philo, 0) == 1)
		return (1);
	if (1 == usleep_check(philo, philo->meta->time_sleep))
		return (1);
	return (0);
}

/*	thinking 
	- prints status and returns immediately
	- returns 1 if end_cycle is 1 (via quick_check_dead)
		when printing status
*/
int	thinking(t_philo *philo)
{
	if (print_status(MAGENTA "is thinking" RESET, philo, 0) == 1)
		return (1);
	return (0);
}

/*	routine sets philos to eat, sleep and think until the philo is dead
	- even numbered philos sleep for 1000 microseconds (= 1 milisecond)
	- philos start eating, sleeping then thinking */
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (1 == philo->meta->num_philos)
		return (single_philo(philo));
	else if (0 == philo->id % 2)
		// usleep(philo->meta->time_eat/2);
		// usleep(60);
	// while (0 == quick_check_dead(philo))
	while (1)
	{
		if (0 == eating(philo))
			if (0 == sleeping(philo))
				thinking(philo);
	}
	return (NULL);
}

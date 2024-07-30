/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 06:28:41 by mateo             #+#    #+#             */
/*   Updated: 2024/07/29 13:05:28 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	drop_forks 'drops' forks using sem_post
	- i = number of forks to drop 
	*/
void	drop_forks(int i, t_philo *philo)
{
	sem_post(philo->forks);
	if (i == 2)
		sem_post(philo->forks);
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
	sem_wait(philo->forks);
	if (print_status(YELLOW "has taken a fork" RESET, philo) == 1)
		return (drop_forks(1, philo), 1);
	sem_wait(philo->forks);
	if (print_status(YELLOW "has taken a fork" RESET, philo) == 1)
		return (drop_forks(2, philo), 1);
	if (print_status(GREEN "is eating" RESET, philo) == 1)
		return (drop_forks(2, philo), 1);
	sem_wait(philo->meal_sem);
	philo->last_meal = time_now_ms();
	philo->eating = 1;
	sem_post(philo->meal_sem);
	if (1 == usleep_check(philo, philo->meta->time_eat))
	{
		
		drop_forks(2, philo);
		exit (PHILO_DEAD);
		// return (drop_forks(2, philo), 1);
	}

	drop_forks(2, philo);
	sem_wait(philo->meal_sem);
	philo->num_meals++;
	philo->eating = 0;
	if (philo->meta->min_meals != 0 && philo->num_meals >= philo->meta->min_meals)
	{
		sem_post(philo->meal_sem);
		destroy_local_sem(philo->meta, philo->meta->num_philos, 0);
		exit (PHILO_FULL);
	}
	sem_post(philo->meal_sem);
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
	if (print_status(BLUE "is sleeping" RESET, philo) == 1)
	{
		exit (PHILO_DEAD);
		// return (1);
	}
	if (1 == usleep_check(philo, philo->meta->time_sleep))
	{
		exit (PHILO_DEAD);
		// return (1);
	}
	return (0);
}

/*	thinking 
	- prints status and returns immediately
	- returns 1 if end_cycle is 1 (via quick_check_dead)
		when printing status
*/
int	thinking(t_philo *philo)
{
	if (print_status(MAGENTA "is thinking" RESET, philo) == 1)
		exit (PHILO_DEAD);
		// return (1);
	return (0);
}

/*	routine sets philos to eat, sleep and think until the philo is dead
	- even numbered philos sleep for 1000 microseconds (= 1 milisecond)
	- philos start eating, sleeping then thinking */
int	routine(t_meta *meta, int i)
{
	t_philo	*philo;

	philo = meta->philos[i];
	if (pthread_create(&philo->check_end, NULL, &monitor, philo) != 0)
		exit (-1); // update error 
	if (1 == philo->meta->num_philos)
	{
		exit (single_philo(philo));
	}
	else if (0 == philo->id % 2)
		usleep(1000);
	while (0 == quick_check_dead(philo))
	{
		if (0 == eating(philo))
			if (0 == sleeping(philo))
				thinking(philo);
	}
	pthread_join(philo->check_end, NULL);
	exit (0);
}

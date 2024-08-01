/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 06:28:41 by mateo             #+#    #+#             */
/*   Updated: 2024/07/31 13:39:41 by mateo            ###   ########.fr       */
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
	print_status(YELLOW "has taken a fork" RESET, philo, 0);
	sem_wait(philo->forks);
	print_status(YELLOW "has taken a fork" RESET, philo, 0);
	print_status(GREEN "is eating" RESET, philo, 0);
	sem_wait(philo->meal_local);
	philo->last_meal = time_now_ms();
	philo->eating = 1;
	// dprintf(2, "%d->last_meal: %ld\n", philo->id, philo->last_meal);
	sem_post(philo->meal_local);
	usleep_check(philo, philo->meta->time_eat);
	drop_forks(2, philo);
	sem_wait(philo->meal_local);
	philo->num_meals++;
	philo->eating = 0;
	if (philo->meta->min_meals != 0 && philo->num_meals >= philo->meta->min_meals)
	{
		sem_post(philo->meal_local);
		// sem_wait(philo->end_local);
		// philo->end_cycle = 1; 
		// sem_post(philo->end_local);
		// pthread_join(philo->check_end, NULL);
		sem_post(philo->end_global);
		while (1) // use a sem_wait to keep processes open
		{
		}
		// destroy_local_sem(philo->meta, philo->meta->num_philos, 0); // fix cleanup
		// exit (PHILO_FULL);
	}
	sem_post(philo->meal_local);
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
	print_status(BLUE "is sleeping" RESET, philo, 0);
	usleep_check(philo, philo->meta->time_sleep);
	return (0);
}

/*	thinking 
	- prints status and returns immediately
	- returns 1 if end_cycle is 1 (via quick_check_dead)
		when printing status
*/
int	thinking(t_philo *philo)
{
	print_status(MAGENTA "is thinking" RESET, philo, 0);
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
	while (time_now_ms() <= philo->last_meal)
	{
		usleep(100);
	}
	if (1 == philo->meta->num_philos)
		exit (single_philo(philo));
	else if (0 == philo->id % 2)
		usleep(meta->time_eat * 1000 / 2);
	// while (0 == quick_check_dead(philo))
	while (1)
	{
		if (0 == eating(philo))
			if (0 == sleeping(philo))
				thinking(philo);
	}
	// sem_post(meta->end_global);
	printf("%ld %d %s\n", time_now_ms() - philo->meta->start_time, \
			philo->id, "release end_global\n");
	while (1);
	// pthread_join(philo->check_end, NULL);
	exit (0);
}

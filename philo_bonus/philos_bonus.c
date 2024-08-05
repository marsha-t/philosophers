/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 06:28:41 by mateo             #+#    #+#             */
/*   Updated: 2024/08/05 13:27:46 by mateo            ###   ########.fr       */
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
void	eating(t_philo *philo)
{
	sem_wait(philo->forks);
	print_status(YELLOW "has taken a fork" RESET, philo, 0);
	sem_wait(philo->forks);
	print_status(YELLOW "has taken a fork" RESET, philo, 0);
	print_status(GREEN "is eating" RESET, philo, 0);
	sem_wait(philo->meal_local);
	philo->last_meal = philo->last_status;
	philo->eating = 1;
	sem_post(philo->meal_local);
	usleep_check(philo, philo->meta->time_eat);
	drop_forks(2, philo);
	sem_wait(philo->meal_local);
	philo->num_meals++;
	philo->eating = 0;
	if (philo->meta->min_meals != 0 && \
		philo->num_meals >= philo->meta->min_meals)
	{
		sem_post(philo->end_global);
		while (1)
		{
		}
	}
	sem_post(philo->meal_local);
}

/*	sleeping 
	- order
		- prints status 
		- pauses philo for time_sleep
	- returns 1 if end_cycle is 1 (via quick_check_dead)
		when printing status or sleeping */
void	sleeping(t_philo *philo)
{
	print_status(BLUE "is sleeping" RESET, philo, 0);
	usleep_check(philo, philo->meta->time_sleep);
}

/*	thinking 
	- prints status and returns immediately
	- returns 1 if end_cycle is 1 (via quick_check_dead)
		when printing status
*/
void	thinking(t_philo *philo)
{
	print_status(MAGENTA "is thinking" RESET, philo, 0);
}

/*	routine sets philos to eat, sleep and think until the philo is dead
	- even numbered philos sleep for 1000 microseconds (= 1 milisecond)
	- philos start eating, sleeping then thinking */
void	routine(t_meta *meta, int i)
{
	t_philo	*philo;

	philo = meta->philos[i];
	if (pthread_create(&philo->check_end, NULL, &monitor, philo) != 0)
	{
		sem_post_end(meta->num_philos, meta);
		exit (1);
	}
	while (time_now_ms() <= philo->last_meal)
	{
		usleep(100);
	}
	if (1 == philo->meta->num_philos)
		exit (single_philo(philo));
	else if (0 == philo->id % 2)
		usleep(meta->time_eat * 1000 / 2);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

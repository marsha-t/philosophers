/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:22:30 by mateo             #+#    #+#             */
/*   Updated: 2024/07/31 11:58:05 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_dead(t_philo *philo)
{
	// new
	// sem_wait(philo->end_local); 
	// if (philo->end_cycle == 1)
	// 	return (sem_post(philo->end_local), 1);
	// sem_post(philo->end_local);
	// end new
	sem_wait(philo->meal_local);
	time_t time_now = time_now_ms() ;
	// if (0 == philo->eating && time_now_ms() - philo->last_meal >= philo->meta->time_die)
	if (0 == philo->eating && time_now - philo->last_meal >= philo->meta->time_die)
	{
		dprintf(2, "%d: time_now: %ld, last_meal: %ld, difference: %ld\n", philo->id, time_now, philo->last_meal, time_now-philo->last_meal);
		sem_post(philo->meal_local);
		print_status(RED "is dead" RESET, philo, 1);
		// sem_wait(philo->end_local);
		// philo->end_cycle = 1;
		// sem_post(philo->end_local);
		int i = 0;
		while (i < philo->meta->num_philos)
		{
			sem_post(philo->end_global);
			i++;
		}
		return (1);
	}
	sem_post(philo->meal_local);
	return (0);
}

/*	monitor continuously checks whether philosopher is dead
	*/
void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (1 == check_dead(philo))
			break ;
	}
	return (NULL);
}

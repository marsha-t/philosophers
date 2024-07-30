/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:22:30 by mateo             #+#    #+#             */
/*   Updated: 2024/07/30 15:10:14 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_dead(t_philo *philo)
{
	// new
	sem_wait(philo->end_local); 
	if (philo->end_cycle == 1)
		return (sem_post(philo->end_local), 1);
	sem_post(philo->end_local);
	// end new
	sem_wait(philo->meal_local);
	if (0 == philo->eating && \
		time_now_ms() - philo->last_meal >= philo->meta->time_die)
	{
		sem_post(philo->meal_local);
		print_status(RED "is dead" RESET, philo);
		sem_wait(philo->end_local);
		philo->end_cycle = 1;
		sem_post(philo->end_local);
		sem_post(philo->end_global);
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

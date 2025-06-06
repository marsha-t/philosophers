/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:22:30 by mateo             #+#    #+#             */
/*   Updated: 2024/08/05 13:23:04 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sem_post_end(int n, t_meta *meta)
{
	int	i;

	i = 0;
	while (i < n)
	{
		sem_post(meta->end_global);
		i++;
	}
}

int	check_dead(t_philo *philo)
{
	int	i;

	i = 0;
	sem_wait(philo->meal_local);
	if (0 == philo->eating && \
		time_now_ms() - philo->last_meal >= philo->meta->time_die)
	{
		sem_post(philo->meal_local);
		print_status(RED "is dead" RESET, philo, 1);
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
		check_dead(philo);
		usleep(500);
	}
	return (NULL);
}

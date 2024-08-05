/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:22:30 by mateo             #+#    #+#             */
/*   Updated: 2024/08/05 12:54:31 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	check_any_dead checks whether any of the philosophers is dead
	if so, check_dead updates end_cycle and announces it 
	- philo is dead if not eating and time_die > time since last_meal
	- if any dead, updates end_cycle and returns 1 
 */
int	check_any_dead(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->num_philos)
	{
		pthread_mutex_lock(&meta->last_meal_mutex);
		if (0 == meta->philos[i]->eating && \
			time_now_ms() - meta->philos[i]->last_meal >= meta->time_die)
		{
			pthread_mutex_unlock(&meta->last_meal_mutex);
			print_status(RED "is dead" RESET, meta->philos[i]);
			pthread_mutex_lock(&meta->end_mutex);
			meta->end_cycle = 1;
			pthread_mutex_unlock(&meta->end_mutex);
			return (1);
		}
		pthread_mutex_unlock(&meta->last_meal_mutex);
		i++;
	}
	return (0);
}

/*	check_all_full checks whether all the philosophers are full
	and if so, updates end_cycle and returns 1 
	- if no min meal, check_all_full always returns 0 */
int	check_all_full(t_meta *meta)
{
	int	i;

	if (0 == meta->min_meals)
		return (0);
	i = 0;
	while (i < meta->num_philos)
	{
		pthread_mutex_lock(&meta->num_meals_mutex);
		if (meta->philos[i]->num_meals < meta->min_meals)
		{
			pthread_mutex_unlock(&meta->num_meals_mutex);
			return (0);
		}
		pthread_mutex_unlock(&meta->num_meals_mutex);
		i++;
	}
	pthread_mutex_lock(&meta->end_mutex);
	meta->end_cycle = 1;
	pthread_mutex_unlock(&meta->end_mutex);
	return (1);
}

/*	monitor continuously checks whether any philosopher is dead
	or if number of meals is reached */
void	*monitor(void *arg)
{
	t_meta	*meta;

	meta = (t_meta *)arg;
	while (1)
		if (1 == check_any_dead(meta) || 1 == check_all_full(meta))
			break ;
	return (NULL);
}

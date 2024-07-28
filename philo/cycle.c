/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 06:14:31 by mateo             #+#    #+#             */
/*   Updated: 2024/07/24 17:58:53 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	start starts cycle of eating, sleeping and thinking 
	- set start time
	- create monitor thread
	- create philo threads */
int	start(t_meta *meta)
{
	int	i;

	meta->start_time = time_now_ms();
	i = 0;
	while (i < meta->num_philos)
	{
		meta->philos[i]->last_meal = meta->start_time;
		i++;
	}
	if (pthread_create(&meta->check_end, NULL, &monitor, meta) != 0)
		return (destroy_mutexes(meta, 4, ERR_THREAD_CREATE), 1);
	i = 0;
	while (i < meta->num_philos)
	{
		if (pthread_create(&meta->philos[i]->thread, NULL, \
			&routine, meta->philos[i]) != 0)
			return (destroy_threads(meta, i, ERR_THREAD_CREATE), 1);
		i++;
	}
	return (0);
}

/*	stop 'stops' cycle of eating, sleeping and thinking
	- main thread waits for all threads 
	- destroys all when all threads have terminated */
int	stop(t_meta *meta)
{
	int	i;

	i = 0;
	pthread_join(meta->check_end, NULL);
	while (i < meta->num_philos)
	{
		pthread_join(meta->philos[i]->thread, NULL);
		i++;
	}
	destroy_mutexes(meta, 4, NULL);
	return (0);
}

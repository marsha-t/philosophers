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
		return (destroy_all(meta, ERR_THREAD_CREATE, 4), 1);
	i = 0;
	while (i < meta->num_philos)
	{
		if (pthread_create(&meta->philos[i]->thread, NULL, \
			&routine, meta->philos[i]) != 0)
			return (destroy_all(meta, ERR_THREAD_CREATE, 4), 1);
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
	if (pthread_join(meta->check_end, NULL) != 0)
		return (destroy_all(meta, ERR_THREAD_JOIN, 4), 1);
	while (i < meta->num_philos)
	{
		if (pthread_join(meta->philos[i]->thread, NULL) != 0)
			return (destroy_all(meta, ERR_THREAD_JOIN, 4), 1);
		i++;
	}
	destroy_all(meta, NULL, 4);
	return (0);
}

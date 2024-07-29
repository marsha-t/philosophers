/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 06:14:31 by mateo             #+#    #+#             */
/*   Updated: 2024/07/29 13:11:42 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	start starts cycle of eating, sleeping and thinking 
	- set start time
	- create monitor thread
*/
int	start(t_meta *meta)
{
	int	i;
	pid_t	pid;

	meta->start_time = time_now_ms();
	dprintf(2, "start time: %ld\n", meta->start_time);

	i = 0;
	while (i < meta->num_philos)
	{
		meta->philos[i]->last_meal = meta->start_time;
		i++;
	}
	if (pthread_create(&meta->check_end, NULL, &monitor, meta) != 0)
		return (destroy_philos(meta, meta->num_philos, ERR_THREAD_CREATE), 1);
	i = 0;
	while (i < meta->num_philos)
	{
		pid = fork();
		if (pid == -1)
			return (1); // add error function
		else if (pid == 0) // child
		{
			routine(meta, i);
			exit (0);
		}
		else // parent
			meta->philo_pids[i] = pid;
		i++;
	}
	return (0);
}

/*	stop 'stops' cycle of eating, sleeping and thinking
	- main process waits for all philosopher processes
	 */
int	stop(t_meta *meta)
{
	int	i;

	i = 0;
	pthread_join(meta->check_end, NULL);
	while (i < meta->num_philos)
	{
		waitpid(meta->philo_pids[i], NULL, 0);
		i++;
	}
	destroy_philos(meta, meta->num_philos, NULL);
	return (0);
}

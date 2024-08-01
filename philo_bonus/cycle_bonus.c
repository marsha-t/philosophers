/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 06:14:31 by mateo             #+#    #+#             */
/*   Updated: 2024/08/01 15:26:43 by mateo            ###   ########.fr       */
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

	meta->start_time = time_now_ms() + (meta->num_philos * 20);
	i = 0;
	while (i < meta->num_philos)
	{
		meta->philos[i]->last_meal = meta->start_time;
		i++;
	}
	i = 0;
	sem_wait(meta->end_global);
	while (i < meta->num_philos)
	{
		pid = fork();
		if (pid == -1)
			return (1); // add error function: kill philos up until i and then destroy local sem
		else if (pid == 0)
			routine(meta, i);
		else
			meta->philo_pids[i] = pid;
		i++;
	}
	return (0);
}

int	kill_philos(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->num_philos)
	{
		kill(meta->philo_pids[i], SIGKILL);
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
	while (i < meta->num_philos)
	{
		sem_wait(meta->end_global);
		i++;
	}
	kill_philos(meta);
	destroy_local_sem(meta, meta->num_philos, NULL);
	return (0);
}

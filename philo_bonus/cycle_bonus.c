/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 06:14:31 by mateo             #+#    #+#             */
/*   Updated: 2024/08/05 13:25:37 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	start starts cycle of eating, sleeping and thinking 
	- set start time
	- create monitor thread
*/
int	start(t_meta *meta)
{
	int		i;
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
			return (destroy_philo_process(meta, i, ERR_FORK), 1);
		else if (pid == 0)
			routine(meta, i);
		else
			meta->philo_pids[i] = pid;
		i++;
	}
	return (0);
}

/*	kill_philos sends SIGKILL to philos from 0 to n - 1 */
int	kill_philos(t_meta *meta, int n)
{
	int	i;

	i = 0;
	while (i < n)
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
	kill_philos(meta, meta->num_philos);
	destroy_local_sem(meta, meta->num_philos, NULL);
	return (0);
}

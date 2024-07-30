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
	i = 0;
	while (i < meta->num_philos)
	{
		meta->philos[i]->last_meal = meta->start_time;
		i++;
	}
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
	int	status;
	int	exit_status;
	int	num_philo_full;

	i = 0;
	num_philo_full = 0;
	while (1)
	{
		if (waitpid(meta->philo_pids[i], &status, WNOHANG) != 0)
		{
			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				if (exit_status == PHILO_FULL)
				{
					num_philo_full++;
					if (num_philo_full == meta->num_philos)
					{
						break ;
					}
				}
				else if (exit_status == PHILO_DEAD)
				{
					kill_philos(meta);
					break ;
				}
			}
		}
		i++;
		if (i == meta->num_philos)
			i = 0;
	}
	destroy_local_sem(meta, meta->num_philos, NULL);
	return (0);
}

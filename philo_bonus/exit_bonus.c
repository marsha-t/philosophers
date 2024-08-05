/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 06:42:33 by mateo             #+#    #+#             */
/*   Updated: 2024/08/05 13:28:17 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	destroy_philo_process kills nth_philo - 1 child processes
	then calls destroy_local_sem() 
	- nth_philo is where there's error calling fork() */
void	destroy_philo_process(t_meta *meta, int nth_philo, char *str)
{
	kill_philos(meta, nth_philo);
	destroy_local_sem(meta, meta->num_philos, str);
}

/*	destroy_local_sem closes and unlinks the meal_local sem for each philo 
	then calls destroy_philos() 
	- nth_philo is where there's an error opening meal_local sem
*/
void	destroy_local_sem(t_meta *meta, int nth_philo, char *str)
{
	int	i;

	i = 0;
	while (i < nth_philo)
	{
		sem_close(meta->philos[i]->meal_local);
		sem_unlink(meta->philos[i]->meal_local_name);
		i++;
	}
	destroy_philos(meta, meta->num_philos, str);
}

/*	destroy_philos frees the individual philo struct
	and then destroy semaphores
	- nth_philo is the philo that failed malloc
		so free everything prior to it */
void	destroy_philos(t_meta *meta, int nth_philo, char *str)
{
	int	i;

	i = 0;
	while (i < nth_philo)
	{
		safe_free(meta->philos[i]->meal_local_name);
		safe_free(meta->philos[i]);
		i++;
	}
	safe_free(meta->philos);
	destroy_sem(meta, 3, str);
}

/*	destroy_sem closes and unlinks semaphores 
	and then exits with error
	- num_sem is the semaphore that failed to be opened
*/
void	destroy_sem(t_meta *meta, int num_sem, char *str)
{
	if (num_sem >= 1)
		sem_close(meta->forks);
	if (num_sem >= 2)
		sem_close(meta->print_global);
	if (num_sem >= 3)
		sem_close(meta->end_global);
	sem_unlink_all();
	exit_error(str, meta);
}

/*	exit_error:
	- prints an error message
	- frees meta as necessary */
void	exit_error(char *msg, t_meta *meta)
{
	if (msg)
		printf("%s\n", msg);
	if (meta)
	{
		if (meta->philo_pids)
			safe_free(meta->philo_pids);
		safe_free(meta);
	}
}

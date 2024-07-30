/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 06:42:33 by mateo             #+#    #+#             */
/*   Updated: 2024/07/29 12:22:11 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_local_sem(t_meta *meta, int nth_philo, char *str)
{
	int	i;
	i = 0;
	while (i < nth_philo)
	{
		sem_close(meta->philos[i]->meal_sem);
		sem_unlink(meta->philos[i]->meal_sem_name);
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
		safe_free(meta->philos[i]->meal_sem_name);
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
		sem_close(meta->print_sem);
	if (num_sem >= 3)
		sem_close(meta->end_sem);
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

/*	safe_free frees the pointer to allocated memory and
	sets the pointer to null */
void	safe_free(void *memory)
{
	free(memory);
	memory = 0;
}

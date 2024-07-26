/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 06:42:33 by mateo             #+#    #+#             */
/*   Updated: 2024/07/24 11:21:03 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	destroy_all destroys mutexes and then destroy philos
	- num_mutexes is the no. of mutexes created so far
*/
void	destroy_all(t_meta *meta, char *str, int num_mutexes)
{
	if (num_mutexes >= 1)
		pthread_mutex_destroy(&meta->print_mutex);
	if (num_mutexes >= 2)
		pthread_mutex_destroy(&meta->end_mutex);
	if (num_mutexes >= 3)
		pthread_mutex_destroy(&meta->last_meal_mutex);
	if (num_mutexes >= 4)
		pthread_mutex_destroy(&meta->num_meals_mutex);
	destroy_philos(meta, meta->num_philos, str);
}

/*	destroy_philos frees the individual philo struct
	and then destroy forks 
	- nth_philo is the philo that failed malloc 
		so free everything prior to it */
void	destroy_philos(t_meta *meta, int nth_philo, char *str)
{
	int	i;

	i = 0;
	while (i < nth_philo)
	{
		safe_free(meta->philos[i]);
		i++;
	}
	safe_free(meta->philos);
	destroy_forks(meta, meta->num_philos, str);
}

/*	destroy_forks destroys a given number of forks 
	before exiting with error 
	- nth fork is the fork that failed init 
		so destroy everything prior to it */
void	destroy_forks(t_meta *meta, int nth_fork, char *str)
{
	int	i;

	i = 0;
	while (i < nth_fork)
	{
		pthread_mutex_destroy(&meta->forks[i]);
		i++;
	}
	if (meta->forks)
		safe_free(meta->forks);
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
		safe_free(meta);
}

/*	safe_free frees the pointer to allocated memory and 
	sets the pointer to null */
void	safe_free(void *memory)
{
	free(memory);
	memory = 0;
}

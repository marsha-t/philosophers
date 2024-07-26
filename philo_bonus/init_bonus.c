/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:17:16 by mateo             #+#    #+#             */
/*   Updated: 2024/07/24 11:22:19 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	init_forks allocates space for forks and initialises them 
	- returns 1 if error w/ malloc or mutex init */
int	init_forks(t_meta *meta)
{
	int	i;

	meta->forks = malloc(sizeof(pthread_mutex_t) * meta->num_philos);
	if (!meta->forks)
		return (exit_error(ERR_MALLOC_FORKS, meta), 1);
	i = 0;
	while (i < meta->num_philos)
	{
		if (pthread_mutex_init(&meta->forks[i], NULL) != 0)
			return (destroy_forks(meta, i, ERR_MUTEX_INIT), 1);
		i++;
	}
	return (0);
}

/*	init_philo allocates space for each philo and
	- initialises *SOME* starting values
	- assigns forks
	- link back to meta
	It does NOT create threads nor initialise start time  */
t_philo	*init_philo(t_meta *meta, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i + 1;
	philo->num_meals = 0;
	philo->eating = 0;
	philo->end_cycle = &meta->end_cycle;
	philo->fork_l = &meta->forks[i];
	philo->fork_r = &meta->forks[0];
	if (i != meta->num_philos - 1)
	{
		philo->fork_r = &meta->forks[i + 1];
	}
	philo->meta = meta;
	return (philo);
}

/*	init_philos allocates space for pointers for all philosophers and
	- initialises each using another function - init_philo 
	- returns 1 if error w/ malloc */
int	init_philos(t_meta *meta)
{
	int	i;

	meta->philos = malloc(sizeof(t_philo *) * meta->num_philos);
	if (!meta->philos)
		return (destroy_forks(meta, meta->num_philos, ERR_MALLOC_PHILOS), 1);
	i = 0;
	while (i < meta->num_philos)
	{
		meta->philos[i] = init_philo(meta, i);
		if (!meta->philos[i])
			return (destroy_philos(meta, i, ERR_MALLOC_PHILO_I), 1);
		i++;
	}
	return (0);
}

/*	init_oth initialises mutexes and assigns its address in each philo struct
	- mutexes: print_mutex, end_mutex, last_meal_mutex, num_meals_mutex
	- returns 1 if error w/ mutex init */
int	init_oth_mutex(t_meta *meta)
{
	int	i;

	if (pthread_mutex_init(&meta->print_mutex, NULL) != 0)
		return (destroy_philos(meta, meta->num_philos, ERR_MUTEX_INIT), 1);
	if (pthread_mutex_init(&meta->end_mutex, NULL) != 0)
		return (destroy_all(meta, ERR_MUTEX_INIT, 1), 1);
	if (pthread_mutex_init(&meta->last_meal_mutex, NULL) != 0)
		return (destroy_all(meta, ERR_MUTEX_INIT, 2), 1);
	if (pthread_mutex_init(&meta->num_meals_mutex, NULL) != 0)
		return (destroy_all(meta, ERR_MUTEX_INIT, 3), 1);
	i = 0;
	while (i < meta->num_philos)
	{
		meta->philos[i]->print_mutex = &meta->print_mutex;
		meta->philos[i]->end_mutex = &meta->end_mutex;
		meta->philos[i]->last_meal_mutex = &meta->last_meal_mutex;
		meta->philos[i]->num_meals_mutex = &meta->num_meals_mutex;
		i++;
	}
	return (0);
}

/*	init_meta initialises the meta structure with:
	- provided arguments
	- array of forks
	- array of philosophers*/
t_meta	*init_meta(int argc, char **argv)
{
	t_meta	*meta;

	meta = malloc(sizeof(t_meta));
	if (!meta)
		return (exit_error(ERR_MALLOC_META, 0), NULL);
	meta->num_philos = ft_atoi(argv[1]);
	meta->time_die = ft_atoi(argv[2]);
	meta->time_eat = ft_atoi(argv[3]);
	meta->time_sleep = ft_atoi(argv[4]);
	meta->end_cycle = 0;
	meta->min_meals = 0;
	meta->forks = 0;
	meta->philos = 0;
	if (6 == argc)
		meta->min_meals = ft_atoi(argv[5]);
	if (1 == init_forks(meta))
		return (0);
	if (1 == init_philos(meta))
		return (0);
	if (1 == init_oth_mutex(meta))
		return (0);
	return (meta);
}

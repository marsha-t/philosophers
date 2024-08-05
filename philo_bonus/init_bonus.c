/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:17:16 by mateo             #+#    #+#             */
/*   Updated: 2024/08/05 13:28:59 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	init_sem opens all semaphores:
	- semaphores: forks, print, end, last_meal, num_meals
	- removes semaphores if they'd previously existed 
	- returns 1 if error w/ malloc or mutex init */
int	init_sem(t_meta *meta)
{
	sem_unlink_all();
	meta->forks = sem_open("/forks", O_CREAT, 0644, meta->num_philos);
	if (meta->forks == SEM_FAILED)
		return (exit_error(ERR_SEM_OPEN, meta), 1);
	meta->print_global = sem_open("/print", O_CREAT, 0644, 1);
	if (meta->print_global == SEM_FAILED)
		return (destroy_sem(meta, 1, ERR_SEM_OPEN), 1);
	meta->end_global = sem_open("/end", O_CREAT, 0644, 1);
	if (meta->end_global == SEM_FAILED)
		return (destroy_sem(meta, 2, ERR_SEM_OPEN), 1);
	return (0);
}

/*	init_philo allocates space for each philo and
	- initialises *SOME* starting values
	- assigns semaphores
	- link back to meta
	It does NOT create processes nor initialise start time  */
t_philo	*init_philo(t_meta *meta, int i)
{
	t_philo	*philo;
	char	*id_str;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i + 1;
	philo->num_meals = 0;
	philo->eating = 0;
	philo->end_cycle = 0;
	philo->forks = meta->forks;
	philo->print_global = meta->print_global;
	philo->end_global = meta->end_global;
	philo->meta = meta;
	id_str = ft_itoa(i);
	philo->meal_local_name = ft_strjoin("/meal_", id_str);
	safe_free(id_str);
	if (!philo->meal_local_name)
		return (free(philo), NULL);
	return (philo);
}

/*	init_philos allocates space for pointers for all philosophers and
	- initialises each pointer with philo struct using init_philo 
	- returns 1 if error w/ malloc */
int	init_philos(t_meta *meta)
{
	int	i;

	meta->philos = malloc(sizeof(t_philo *) * meta->num_philos);
	if (!meta->philos)
		return (destroy_sem(meta, 3, ERR_MALLOC_PHILOS), 1);
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

/*	init_philo_sem creates a 'local' sem
	- sem controls philo's eating, last_meal and num_meals 
	- sem is 'uniquely' named */
int	init_philo_sem(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->num_philos)
	{
		sem_unlink(meta->philos[i]->meal_local_name);
		meta->philos[i]->meal_local = \
			sem_open(meta->philos[i]->meal_local_name, O_CREAT, 0644, 1);
		if (meta->philos[i]->meal_local == SEM_FAILED)
			return (destroy_local_sem(meta, i, ERR_SEM_OPEN), 1);
		i++;
	}
	return (0);
}

/*	init_meta initialises the meta structure with:
	- provided arguments
	- semaphores
	- array of philosophers structures*/
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
	meta->min_meals = 0;
	meta->forks = 0;
	meta->philos = 0;
	if (6 == argc)
		meta->min_meals = ft_atoi(argv[5]);
	meta->philo_pids = malloc(sizeof(pid_t) * meta->num_philos);
	if (!meta->philo_pids)
		return (exit_error(ERR_MALLOC_PIDS, meta), NULL);
	if (init_sem(meta) == 1)
		return (0);
	if (init_philos(meta) == 1)
		return (0);
	if (init_philo_sem(meta) == 1)
		return (0);
	return (meta);
}

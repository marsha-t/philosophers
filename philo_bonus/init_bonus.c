/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:17:16 by mateo             #+#    #+#             */
/*   Updated: 2024/07/29 10:57:36 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	sem_unlink_all removes all semaphores 
	(in case they already exist) 
	- sem_unlink can return -1 and set errno if sempahore doesn't exist
		so reset errno at end of function
	*/
void	sem_unlink_all(void)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/end");
	sem_unlink("/last_meal");
	sem_unlink("/num_meals");
	errno = 0;
}

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
	meta->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (meta->print_sem == SEM_FAILED)
		return (destroy_sem(meta, 1, ERR_SEM_OPEN), 1);
	meta->end_sem = sem_open("/end", O_CREAT, 0644, 1);
	if (meta->end_sem == SEM_FAILED)
		return (destroy_sem(meta, 2, ERR_SEM_OPEN), 1);
	meta->last_meal_sem = sem_open("/last_meal", O_CREAT, 0644, 1);
	if (meta->last_meal_sem == SEM_FAILED)
		return (destroy_sem(meta, 3, ERR_SEM_OPEN), 1);
	meta->num_meals_sem = sem_open("/num_meals", O_CREAT, 0644, 1);
	if (meta->num_meals_sem == SEM_FAILED)
		return (destroy_sem(meta, 4, ERR_SEM_OPEN), 1);
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

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i + 1;
	philo->num_meals = 0;
	philo->eating = 0;
	philo->end_cycle = &meta->end_cycle;
	philo->forks = meta->forks;
	philo->print_sem = meta->print_sem;
	philo->end_sem = meta->end_sem;
	philo->last_meal_sem = meta->last_meal_sem;
	philo->num_meals_sem = meta->num_meals_sem;
	philo->meta = meta;
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
		return (destroy_sem(meta, 4, ERR_MALLOC_PHILOS), 1);
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
	meta->end_cycle = 0;
	meta->min_meals = 0;
	meta->forks = 0;
	meta->philos = 0;
	if (6 == argc)
		meta->min_meals = ft_atoi(argv[5]);
	meta->philo_pids = malloc(sizeof(pid_t) * meta->num_philos);
	if (!meta->philo_pids)
		return (exit_error(ERR_MALLOC_PIDS, meta), NULL);
	if (init_sem(meta))
		return (0);
	if (1 == init_philos(meta))
		return (0);
	return (meta);
}

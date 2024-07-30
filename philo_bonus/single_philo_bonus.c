/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:46:29 by mateo             #+#    #+#             */
/*   Updated: 2024/07/29 10:53:43 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	single_philo runs the routine for a single philo 
	i.e., pick up fork and die */
int	single_philo(t_philo *philo)
{
	sem_wait(philo->forks);
	print_status("has taken a fork", philo);
	usleep_check(philo, philo->meta->time_die);
	sem_post(philo->forks);
	// sem_close(philo->meal_local);
	// sem_unlink(philo->meal_local_name);
	// destroy_philos(philo->meta, philo->meta->num_philos, 0);
	// dprintf(2, "dead\n");
	return (PHILO_DEAD);
}
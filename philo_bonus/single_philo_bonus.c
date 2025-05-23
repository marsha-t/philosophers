/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:46:29 by mateo             #+#    #+#             */
/*   Updated: 2024/08/05 13:24:32 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	single_philo runs the routine for a single philo 
	i.e., pick up fork and die */
int	single_philo(t_philo *philo)
{
	sem_wait(philo->forks);
	print_status("has taken a fork", philo, 0);
	usleep_check(philo, philo->meta->time_die);
	sem_post(philo->forks);
	return (1);
}

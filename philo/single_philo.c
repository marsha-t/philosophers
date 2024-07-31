/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:46:29 by mateo             #+#    #+#             */
/*   Updated: 2024/07/31 14:02:06 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	single_philo runs the routine for a single philo 
	i.e., pick up fork and die */
void	*single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_status("has taken a fork", philo, 0);
	usleep_check(philo, philo->meta->time_die);
	pthread_mutex_unlock(philo->fork_l);
	return (NULL);
}

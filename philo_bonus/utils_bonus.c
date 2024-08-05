/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:44:24 by mateo             #+#    #+#             */
/*   Updated: 2024/08/05 13:29:10 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*	print_status prints the status of a given philo
	returns 1 if death occurred */
int	print_status(char *str, t_philo *philo, int death)
{
	sem_wait(philo->print_global);
	philo->last_status = time_now_ms();
	printf("%ld %d %s\n", philo->last_status - \
		philo->meta->start_time, philo->id, str);
	if (death == 0)
	{
		sem_post(philo->print_global);
		return (0);
	}
	return (1);
}

/*	usleep_check 'sleeps' for ms MILIseconds
	- checks during sleep whether end conditions have been reached
	It accounts for time used for checking */
int	usleep_check(t_philo *philo, time_t ms)
{
	time_t	start;

	start = time_now_ms();
	while (time_now_ms() - start < ms)
	{
		(void)philo;
		usleep(100);
	}
	return (0);
}

/*	time_now_ms	returns no. of MILIseconds since epoch*/
time_t	time_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*	safe_free frees the pointer to allocated memory and
	sets the pointer to null */
void	safe_free(void *memory)
{
	free(memory);
	memory = 0;
}

/*	sem_unlink_all removes all semaphores (incl global AND local)
	(in case they already exist) 
	- sem_unlink can return -1 and set errno if sempahore doesn't exist
		so reset errno at end of function
	*/
void	sem_unlink_all(void)
{
	int		i;
	char	*id_str;
	char	*meal_local_name;

	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/end");
	i = 0;
	while (i < 200)
	{
		id_str = ft_itoa(i);
		meal_local_name = ft_strjoin("/meal_", id_str);
		sem_unlink(meal_local_name);
		safe_free(id_str);
		safe_free(meal_local_name);
		i++;
	}
	errno = 0;
}

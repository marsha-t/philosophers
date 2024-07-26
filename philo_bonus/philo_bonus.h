/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 06:37:31 by mateo             #+#    #+#             */
/*   Updated: 2024/04/20 07:43:13 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_meta
{
	int				num_philos;
	time_t			time_die;
	time_t			time_eat;
	time_t			time_sleep;
	int				min_meals;
	time_t			start_time;
	int				end_cycle;
	pthread_mutex_t	*forks;
	t_philo			**philos;
	pthread_t		check_end;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	num_meals_mutex;
}	t_meta;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				num_meals;
	time_t			last_meal;
	int				eating;	
	int				*end_cycle;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*end_mutex;
	pthread_mutex_t	*last_meal_mutex;
	pthread_mutex_t	*num_meals_mutex;
	t_meta			*meta;
}	t_philo;

/* Error Messages */
# define ERR_ARGS "Wrong number of arguments"
# define ERR_INVALID "Invalid input"
# define ERR_MALLOC_META "Malloc error for meta"
# define ERR_MALLOC_FORKS "Malloc error for forks"
# define ERR_MALLOC_PHILOS "Malloc error for philos"
# define ERR_THREAD_CREATE "Error creating threads"
# define ERR_THREAD_JOIN "Error joining threads"
# define ERR_MUTEX_INIT "Error initialising mutex"

/* utils.c */
int				print_status(char *str, t_philo *philo);
int				usleep_check(t_philo *philo, time_t ms);
time_t			time_now_ms(void);

/*	exit.c*/
void			destroy_all(t_meta *meta, char *str, int num_mutexes);
void			destroy_forks(t_meta *meta, int n, char *str);
void			exit_error(char *msg, t_meta *meta);
void			safe_free(void *memory);

/* parse.c */
int				only_digits(char *str);
int				ft_atoi(const char *str);
int				check_arg(int argc, char **argv);

/* init.c */
t_philo			*init_philo(t_meta *meta, int i);
int				init_philos(t_meta *meta);
int				init_oth_mutex(t_meta *meta);
t_meta			*init_meta(int argc, char **argv);

/* forks.c */
int				init_forks(t_meta *meta);

/* actions.c */
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
int				thinking(t_philo *philo);

/* simulation.c */
void			*single_philo(t_philo *philo);
void			*routine(void *arg);
int				start(t_meta *meta);
int				stop(t_meta *meta);

/* monitor.c */
int				quick_check_dead(t_philo *philo);
// int				check_dead(t_philo *philo);
void			*monitor(void *arg);

/* main.c */

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 06:37:31 by mateo             #+#    #+#             */
/*   Updated: 2024/07/24 11:55:24 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\x1b[0m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"

/****************************************************************************/
/* Error Messages 															*/
/****************************************************************************/
# define ERR_ARGS "Wrong number of arguments"
# define ERR_INVALID "Invalid input"
# define ERR_MALLOC_META "Malloc error for meta"
# define ERR_MALLOC_FORKS "Malloc error for forks"
# define ERR_MALLOC_PHILOS "Malloc error for philos"
# define ERR_MALLOC_PHILO_I "Malloc error for philo[i]"
# define ERR_THREAD_CREATE "Error creating threads"
# define ERR_THREAD_JOIN "Error joining threads"
# define ERR_MUTEX_INIT "Error initialising mutex"

/****************************************************************************/
/* Structures																*/
/****************************************************************************/
typedef struct s_philo	t_philo;

typedef struct s_meta
{
	int					num_philos;
	time_t				time_die;
	time_t				time_eat;
	time_t				time_sleep;
	int					min_meals;
	time_t				start_time;
	int					end_cycle;
	pthread_mutex_t		*forks;
	t_philo				**philos;
	pthread_t			check_end;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		end_mutex;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		num_meals_mutex;
}						t_meta;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					num_meals;
	time_t				last_meal;
	int					eating;
	int					*end_cycle;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*print_mutex;
	pthread_mutex_t		*end_mutex;
	pthread_mutex_t		*last_meal_mutex;
	pthread_mutex_t		*num_meals_mutex;
	t_meta				*meta;
}						t_philo;

/****************************************************************************/
/* Function Declarations													*/
/****************************************************************************/
/* Checking of input: check.c */
int						only_digits(char *str);
int						ft_atoi(const char *str);
int						check_arg(int argc, char **argv);

/* Initialise simulation: init.c */
int						init_forks(t_meta *meta);
t_philo					*init_philo(t_meta *meta, int i);
int						init_philos(t_meta *meta);
int						init_oth_mutex(t_meta *meta);
t_meta					*init_meta(int argc, char **argv);

/*	Clear resources: free and destroy: exit.c*/
void					destroy_threads(t_meta *meta, int num_thread,
							char *str);
void					destroy_mutexes(t_meta *meta, int num_mutexes,
							char *str);
void					destroy_philos(t_meta *meta, int nth_philo, char *str);
void					destroy_forks(t_meta *meta, int nth_fork, char *str);
void					exit_error(char *msg, t_meta *meta);
void					safe_free(void *memory);

/* Functions for monitor thread: monitor.c */
int						check_any_dead(t_meta *meta);
int						check_all_full(t_meta *meta);
void					*monitor(void *arg);

/* Functions for philosophers: philos.c */
void					unlock_forks(int i, t_philo *philo);
int						eating(t_philo *philo);
int						sleeping(t_philo *philo);
int						thinking(t_philo *philo);
void					*routine(void *arg);

/* Starting and stopping cycle: cycle.c */
int						start(t_meta *meta);
int						stop(t_meta *meta);

/* Functions for single philosopher: single_philo.c */
void					*single_philo(t_philo *philo);

/* Utility functions: utils.c */
int						quick_check_dead(t_philo *philo);
int						print_status(char *str, t_philo *philo);
int						usleep_check(t_philo *philo, time_t ms);
time_t					time_now_ms(void);

#endif
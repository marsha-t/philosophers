/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 06:37:31 by mateo             #+#    #+#             */
/*   Updated: 2024/08/01 15:33:25 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

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
# define ERR_SEM_OPEN "Error calling sem_open"

# define ERR_MALLOC_META "Malloc error for meta"
# define ERR_MALLOC_FORKS "Malloc error for forks"
# define ERR_MALLOC_PIDS "Malloc error for philo_pids"
# define ERR_MALLOC_PHILOS "Malloc error for philos"
# define ERR_MALLOC_PHILO_I "Malloc error for philo[i]"

# define ERR_THREAD_CREATE "Error creating threads"
# define ERR_THREAD_JOIN "Error joining threads"

/****************************************************************************/
/* Return Values 															*/
/****************************************************************************/
# define PHILO_FULL 2
# define PHILO_DEAD 3
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
	t_philo				**philos;
	pid_t				*philo_pids;
	sem_t				*forks;
	sem_t				*print_global;
	sem_t				*end_global;
}						t_meta;

typedef struct s_philo
{
	int					id;
	int					num_meals;
	time_t				last_meal;
	time_t			last_status;
	// time_t				end_eat;
	// time_t				end_sleep;
	// time_t				end_think;
	int					eating;
	int					end_cycle;
	pthread_t			check_end;
	sem_t		*forks;
	sem_t		*print_global;
	sem_t		*end_global;
	char		*meal_local_name;
	sem_t		*meal_local;
	t_meta				*meta;
}						t_philo;

/****************************************************************************/
/* Function Declarations													*/
/****************************************************************************/
/* Checking of input: check_bonus.c */
int						only_digits(char *str);
int						ft_atoi(const char *str);
int						check_arg(int argc, char **argv);

/* Initialise simulation: init_bonus.c */
void	sem_unlink_all(void);
int	init_sem(t_meta *meta);
t_philo	*init_philo(t_meta *meta, int i);
int	init_philos(t_meta *meta);
t_meta	*init_meta(int argc, char **argv);

/*	Clear resources: free and destroy: exit_bonus.c*/
void	destroy_local_sem(t_meta *meta, int nth_philo, char *str);
void	destroy_philos(t_meta *meta, int nth_philo, char *str);
void	destroy_sem(t_meta *meta, int num_sem, char *str);
void	exit_error(char *msg, t_meta *meta);
void					safe_free(void *memory);

/* Functions for monitor thread: monitor.c */
int	check_any_dead(t_meta *meta);
int	check_all_full(t_meta *meta);
void	*monitor(void *arg);

/* Functions for philosophers: philos_bonus.c */
void	drop_forks(int i, t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	routine(t_meta *meta, int i);

/* Starting and stopping cycle: cycle_bonus.c */
int	start(t_meta *meta);
int	stop(t_meta *meta);

/* Functions for single philosopher: single_philo_bonus.c */
int	single_philo(t_philo *philo);

/* Utility functions: utils_bonus.c */
int	quick_check_dead(t_philo *philo);
int	print_status(char *str, t_philo *philo, int death);

int	usleep_check(t_philo *philo, time_t ms);
time_t	time_now_ms(void);

/*	Libft functions: libft_bonus.c */
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
#endif
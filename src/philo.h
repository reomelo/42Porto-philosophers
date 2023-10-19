/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:25:14 by riolivei          #+#    #+#             */
/*   Updated: 2023/10/19 17:25:14 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ARG_ERROR "Invalid argument"
# define FORK_ERROR "There was a problem creating forks"
# define PHILOS_ERROR "There was a problem creating philos"
# define THREAD_ERROR "There was a problem creating threads"
# define JOIN_ERROR "There was a problem in join_threads"
# define MALLOC_ERROR "Couldn't allocate memory"

typedef struct s_philo
{
	int						philo_id;
	int						times_eat;
	long long				last_meal_time;
	pthread_t				philo;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			lock_live;
	struct s_data			*data;
}	t_philo;

typedef struct s_data
{
	int					n_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					times_must_eat;
	int					dead;
	int					satisfied;
	long long			time_start;
	t_philo				*all_philos;
	pthread_mutex_t		lock_print;
	pthread_mutex_t		lock_verify;
	pthread_mutex_t		*forks;
	pthread_t			supervise;
}	t_data;

typedef enum e_event_n
{
	EATIN,
	SLEEPIN,
	THINKIN,
	TAKE_F,
	DEAD,
}	t_event_n;

/*philo.c*/

void		end_of_the_world(t_data *data);
int			check_args(int argc, char **argv);
void		init(t_data *data, int argc, char **argv);

/*the_beginning.c*/

int			the_beginning(t_data *data);
int			forks_creation(t_data *data);
int			philos_creation(t_data *data);
int			threads_creation(t_data *data);
int			join_threads(t_data *data);

/*action.c*/

void		*action(void *philo_id);
void		print(t_philo *philo, t_event_n event_n);
void		*supervise(void *thread);
int			is_dead(t_data *data);
int			everyone_ate(t_data *data);

/*action2.c*/

int			take_forks(t_philo *philo);
int			eat_(t_philo *philo);
void		eat2_(t_philo *philo);
int			sleep_(t_philo *philo);
int			think_(t_philo *philo);

/*utils.c*/

int			is_digit(int nbr);
int			is_num(char **argv);
int			is_big(int argc, char **argv);
long		ft_atoi(const char *str);

/*utils.2*/

size_t		len(char *str);
void		error_msg(char *error_msg);
suseconds_t	get_time(void);

#endif

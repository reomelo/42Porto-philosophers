/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:57:41 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/21 18:17:32 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_args{
	int				nphilos;
	int				nmeals;
	long int		tdie;
	long int		teat;
	long int		tsleep;
}				t_args;

typedef struct s_philos{
	pthread_t		id;
	int				meals;
	int				n;
	long int		last_meal;
	pthread_mutex_t	eating;
	struct s_values	*values;
}				t_philos;

typedef struct s_values{
	long int		start_time;
	bool			deaths;
	bool			print;
	t_args			args;
	t_philos		*philos;
	pthread_mutex_t	*forks;
}				t_values;

//UTILS.C
long int	ft_atoi(const char *str);
int			errors(int argc, char *argv[]);
void		initiate(char *argv[], t_values	*values);
long int	get_time(void);

//UTILS2.C
void		free_all_stacks(t_values *values, char c);
int			locking(t_philos *philos);

//ACTIONS.C
void		thinking(t_philos *philos);
int			forking(t_philos *philos);
void		eating(t_philos *philos);
void		sleeping(t_philos *philos);
void		dying(t_philos *philos);

#endif
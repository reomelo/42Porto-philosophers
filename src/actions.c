/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:02:12 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/21 23:47:10 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dying(t_philos *philos)
{
	printf("%ld %d %s\n", get_time() - philos->values->start_time,
		philos->n, DIED);
}

void	thinking(t_philos *philos)
{
	if (philos->values->print)
		printf("%ld %d %s\n", get_time() - philos->values->start_time,
			philos->n, THINK);
}

int	forking(t_philos *philos)
{
	int			fork;
	
	if (philos->values->deaths || !meals_left(philos->values))	
		return (0);
	pthread_mutex_lock(&philos->values->forks[philos->n - 1]);
	printf("%ld %d %s\n", get_time() - philos->values->start_time,
		philos->n, FORK);
	if (philos->n - 1 == 0)
		fork = philos->values->args.nphilos - 1;
	else
		fork = philos->n - 2;
	pthread_mutex_lock(&philos->values->forks[fork]);
	printf("%ld %d %s\n", get_time() - philos->values->start_time,
		philos->n, FORK);
	return (1);
}

void	eating(t_philos *philos)
{
	pthread_mutex_lock(&philos->eating);
	philos->last_meal = get_time();
	pthread_mutex_unlock(&philos->eating);
	printf("%ld %d %s\n", get_time() - philos->values->start_time,
		philos->n, EAT);
	usleep(philos->values->args.teat * 1000);
	philos->meals--;
	pthread_mutex_unlock(&philos->values->forks[philos->n - 1]);
	if (philos->n - 1 == 0)
		pthread_mutex_unlock(&philos->values->forks[philos
			->values->args.nphilos - 1]);
	else
		pthread_mutex_unlock(&philos->values->forks[philos->n - 2]);
}

void	sleeping(t_philos *philos)
{
	printf("%ld %d %s\n", get_time() - philos->values->start_time,
		philos->n, SLEEP);
	usleep(philos->values->args.tsleep * 1000);
}

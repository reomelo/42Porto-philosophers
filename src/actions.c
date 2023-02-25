/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:02:12 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/25 01:19:27 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dying(t_philos *philos)
{
	pthread_mutex_lock(&philos->values->is_dead);
	philos->values->deaths = true;
	pthread_mutex_unlock(&philos->values->is_dead);
	message(philos, DIED);
}

void	thinking(t_philos *philos)
{
	message(philos, THINK);
}

int	forking(t_philos *philos)
{
	int			fork;

	pthread_mutex_lock(&philos->values->is_dead);
	if (philos->values->deaths || philos->values->finished)
	{
		pthread_mutex_unlock(&philos->values->is_dead);
		return (0);
	}
	pthread_mutex_unlock(&philos->values->is_dead);
	pthread_mutex_lock(&philos->values->forks[philos->n - 1]);
	message(philos, FORK);
	if (philos->n - 1 == 0)
		fork = philos->values->args.nphilos - 1;
	else
		fork = philos->n - 2;
	if (check_death(philos, fork))
		return (0);
	pthread_mutex_lock(&philos->values->forks[fork]);
	message(philos, FORK);
	return (1);
}

void	eating(t_philos *philos)
{
	int	fork;

	message(philos, EAT);
	pthread_mutex_lock(&philos->eating);
	philos->meals--;
	philos->last_meal = get_time();
	pthread_mutex_unlock(&philos->eating);
	usleep(philos->values->args.teat * 1000);
	pthread_mutex_unlock(&philos->values->forks[philos->n - 1]);
	if (philos->n - 1 == 0)
		fork = philos->values->args.nphilos - 1;
	else
		fork = philos->n - 2;
	pthread_mutex_unlock(&philos->values->forks[fork]);
}

void	sleeping(t_philos *philos)
{
	message(philos, SLEEP);
	usleep(philos->values->args.tsleep * 1000);
}

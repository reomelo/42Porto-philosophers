/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:02:12 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/22 18:54:10 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dying(t_philos *philos)
{
	message(philos, DIED);
	pthread_mutex_lock(&philos->values->is_dead);
	philos->values->deaths = true;
	philos->values->print = false;
	pthread_mutex_unlock(&philos->values->is_dead);
}

void	thinking(t_philos *philos)
{
	message(philos, THINK);
}

int	forking(t_philos *philos)
{
	int			fork;
	
	if (philos->values->deaths || philos->values->finished)
		return (0);
	pthread_mutex_lock(&philos->values->forks[philos->n - 1]);
	message(philos, FORK);
	if (philos->n - 1 == 0)
		fork = philos->values->args.nphilos - 1;
	else
		fork = philos->n - 2;
	pthread_mutex_lock(&philos->values->forks[fork]);
	message(philos, FORK);
	return (1);
}

void	eating(t_philos *philos)
{
	int fork;
	
	pthread_mutex_lock(&philos->eating);
	philos->last_meal = get_time();
	message(philos, EAT);
	usleep(philos->values->args.teat * 1000);
	pthread_mutex_unlock(&philos->eating);
	philos->meals--;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:29:46 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/23 19:01:16 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philos *philos, int fork)
{
	pthread_mutex_lock(&philos->values->is_dead);
	if (philos->values->deaths || philos->values->finished)
	{
		pthread_mutex_unlock(&philos->values->is_dead);
		pthread_mutex_unlock(&philos->values->forks[philos->n-1]);
		pthread_mutex_unlock(&philos->values->forks[fork]);
		return (1);
	}
	pthread_mutex_unlock(&philos->values->is_dead);
	return (0);
}

int	died(t_philos *philos, int *count)
{
	long int	time;
	
	pthread_mutex_lock(&philos->eating);
	time = get_time() - philos->last_meal;
	pthread_mutex_unlock(&philos->eating);
	if (time >= philos->values->args.tdie)
	{
		dying(philos);
		return (1);
	}
	pthread_mutex_lock(&philos->eating);
	if (philos->meals <= 0)
		(*count)++;
	pthread_mutex_unlock(&philos->eating);
	return (0);
}

void	message(t_philos *philos, char *str)
{
	long int	time;
	
	time = get_time() - philos->values->start_time;
	printf("%ld %d %s\n", time, philos->n, str);
}

void	free_all_stacks(t_values *values, char c)
{
	if (c == 'f')
	{
		free(values->philos);
		free(values->forks);
	}
	free(values);
}

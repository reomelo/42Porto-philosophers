/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:29:46 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/22 18:41:56 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	died(t_philos *philos, int *count)
{
	long int	time;
	pthread_mutex_lock(&philos->eating);
	time = get_time() - philos->last_meal;
	pthread_mutex_unlock(&philos->eating);
	if (time >= philos->values->args.tdie)
	{
		pthread_mutex_lock(&philos->values->is_dead);
		philos->values->deaths = true;
		pthread_mutex_unlock(&philos->values->is_dead);
		dying(philos);
		return (1);
	}
	pthread_mutex_lock(&philos->is_dying);
	if (philos->meals <= 0)
		(*count)++;
	pthread_mutex_unlock(&philos->is_dying);
	return (0);
}

void	message(t_philos *philos, char *str)
{
	long int	time;
	
	if (philos->values->print)
	{
		time = get_time() - philos->values->start_time;
		printf("%ld %d %s\n", time, philos->n, str);
	}
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

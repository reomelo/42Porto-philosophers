/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_beginning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:25:20 by riolivei          #+#    #+#             */
/*   Updated: 2023/10/19 17:25:21 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->all_philos[i].philo, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(data->supervise, NULL) != 0)
		return (1);
	return (0);
}

int	threads_creation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->all_philos[i].philo, NULL, &action,
				&data->all_philos[i]) != 0)
			return (1);
		usleep(2000);
		i++;
	}
	if (pthread_create(&data->supervise, NULL, &supervise, data) != 0)
		return (1);
	return (0);
}

int	philos_creation(t_data *data)
{
	int	i;

	i = 0;
	data->all_philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->all_philos)
		return (1);
	while (i < data->n_philo)
	{
		data->all_philos[i].philo_id = i + 1;
		data->all_philos[i].times_eat = 0;
		data->all_philos[i].last_meal_time = get_time();
		data->all_philos[i].right_fork = &data->forks[i];
		if (i == (data->n_philo - 1))
			data->all_philos[i].left_fork = &data->forks[0];
		else
			data->all_philos[i].left_fork = &data->forks[i + 1];
		data->all_philos[i].data = data;
		if (pthread_mutex_init(&data->all_philos[i].lock_live, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	forks_creation(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->n_philo));
	if (!data->forks)
		return (1);
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->lock_verify, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->lock_print, NULL) != 0)
		return (1);
	return (0);
}

int	the_beginning(t_data *data)
{
	if (forks_creation(data) != 0)
	{
		error_msg(FORK_ERROR);
		return (0);
	}
	if (philos_creation(data) != 0)
	{
		error_msg(PHILOS_ERROR);
		return (0);
	}
	if (threads_creation(data) != 0)
	{
		error_msg(THREAD_ERROR);
		return (0);
	}
	if (join_threads(data) != 0)
	{
		error_msg(JOIN_ERROR);
		return (0);
	}
	return (0);
}

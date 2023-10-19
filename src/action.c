/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:24:50 by riolivei          #+#    #+#             */
/*   Updated: 2023/10/19 17:24:52 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define EAT_N "is eating\n"
#define SLEEP_N "is sleeping\n"
#define THINK_N "is thinking\n"
#define TAKE_F_N "has taken a fork\n"
#define DEAD_N "died\n"

void	*action(void *philo_id)
{
	t_philo	*philo;

	philo = (t_philo *)philo_id;
	if (philo->data->n_philo == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, TAKE_F);
		pthread_mutex_unlock(philo->right_fork);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		usleep(2000);
	while (1)
	{
		if (take_forks(philo) == 1)
			return (NULL);
		if (eat_(philo) == 1)
			return (NULL);
		if (sleep_(philo) == 1)
			return (NULL);
		if (think_(philo) == 1)
			return (NULL);
	}
}

void	print(t_philo *philo, t_event_n event_n)
{
	long long	time;
	const char	*write[5] = {EAT_N, SLEEP_N, THINK_N,
		TAKE_F_N, DEAD_N};

	pthread_mutex_lock(&philo->data->lock_print);
	pthread_mutex_lock(&philo->data->lock_verify);
	if (philo->data->dead != 0
		|| philo->data->satisfied == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->lock_verify);
		pthread_mutex_unlock(&philo->data->lock_print);
		return ;
	}
	time = get_time() - philo->data->time_start;
	printf("%lld %d %s", time, philo->philo_id, write[event_n]);
	pthread_mutex_unlock(&philo->data->lock_verify);
	pthread_mutex_unlock(&philo->data->lock_print);
}

int	is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->all_philos[i].lock_live);
		if (get_time() - data->all_philos[i].last_meal_time > data->time_die)
		{
			print(&data->all_philos[i], DEAD);
			pthread_mutex_lock(&data->lock_verify);
			data->dead++;
			pthread_mutex_unlock(&data->lock_verify);
			pthread_mutex_unlock(&data->all_philos[i].lock_live);
			return (0);
		}
		pthread_mutex_unlock(&data->all_philos[i].lock_live);
		i++;
	}
	return (1);
}

int	everyone_ate(t_data *data)
{
	pthread_mutex_lock(&data->lock_verify);
	if (data->satisfied == data->n_philo)
	{
		pthread_mutex_unlock(&data->lock_verify);
		return (0);
	}
	pthread_mutex_unlock(&data->lock_verify);
	return (1);
}

void	*supervise(void *thread)
{
	t_data	*data;

	data = (t_data *)thread;
	while (1)
	{
		if (is_dead(data) == 0)
			return (NULL);
		if (data->times_must_eat != 0)
			if (everyone_ate(data) == 0)
				return (NULL);
	}
}

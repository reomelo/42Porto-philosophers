/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:24:58 by riolivei          #+#    #+#             */
/*   Updated: 2023/10/19 17:25:01 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->lock_verify))
		return (1);
	if (philo->data->dead != 0
		|| philo->data->satisfied == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->lock_verify);
	}
	pthread_mutex_unlock(&philo->data->lock_verify);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, TAKE_F);
		pthread_mutex_lock(philo->left_fork);
		print(philo, TAKE_F);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, TAKE_F);
		pthread_mutex_lock(philo->right_fork);
		print(philo, TAKE_F);
	}
	return (0);
}

int	eat_(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_verify);
	if (philo->data->dead != 0
		|| philo->data->satisfied == philo->data->n_philo)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->data->lock_verify);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock_verify);
	eat2_(philo);
	return (0);
}

void	eat2_(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_live);
	print(philo, EATIN);
	philo->last_meal_time = get_time();
	pthread_mutex_lock(&philo->data->lock_verify);
	if (philo->data->times_must_eat != 0)
	{
		philo->times_eat++;
		if (philo->times_eat == philo->data->times_must_eat)
			philo->data->satisfied++;
	}
	pthread_mutex_unlock(&philo->data->lock_verify);
	pthread_mutex_unlock(&philo->lock_live);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	sleep_(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_verify);
	if (philo->data->dead != 0
		|| philo->data->satisfied == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->lock_verify);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock_verify);
	print(philo, SLEEPIN);
	usleep(philo->data->time_sleep * 1000);
	return (0);
}

int	think_(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_verify);
	if (philo->data->dead != 0
		|| philo->data->satisfied == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->lock_verify);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock_verify);
	print(philo, THINKIN);
	return (0);
}

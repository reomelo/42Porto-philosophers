/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:25:09 by riolivei          #+#    #+#             */
/*   Updated: 2023/10/19 17:25:09 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_of_the_world(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->all_philos[i].lock_live);
		i++;
	}
	pthread_mutex_destroy(&data->lock_verify);
	pthread_mutex_destroy(&data->lock_print);
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		error_msg(ARG_ERROR);
		return (1);
	}
	if (is_num(argv) != 0)
	{
		error_msg(ARG_ERROR);
		return (1);
	}
	if (is_big(argc, argv) != 0)
	{
		error_msg(ARG_ERROR);
		return (1);
	}
	return (0);
}

void	init(t_data *data, int argc, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	else
		data->times_must_eat = 0;
	data->time_start = get_time();
	data->dead = 0;
	data->satisfied = 0;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_args(argc, argv) != 0)
		return (0);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		error_msg(MALLOC_ERROR);
	init(data, argc, argv);
	the_beginning(data);
	end_of_the_world(data);
	free(data->all_philos);
	free(data->forks);
	free(data);
	return (0);
}

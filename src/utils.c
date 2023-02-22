/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:48:38 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/22 18:10:10 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

long int	ft_atoi(const char *str)
{
	long int	res;
	int			signal;
	int			i;

	res = 0;
	signal = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + (str[i] - '0'));
		i++;
	}
	return (res * signal);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	errors(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
	}
	return (0);
}

void	initiate(char *argv[], t_values *values)
{
	int	i;

	values->args.nphilos = (int)ft_atoi(argv[1]);
	values->args.tdie = ft_atoi(argv[2]);
	values->args.teat = ft_atoi(argv[3]);
	values->args.tsleep = ft_atoi(argv[4]);
	values->forks = malloc(values->args.nphilos * sizeof(pthread_mutex_t));
	values->philos = malloc(values->args.nphilos * sizeof(t_philos));
	values->args.nmeals = INT_MAX;
	values->deaths = false;
	values->finished = false;
	values->print = true;
	pthread_mutex_init(&values->is_dead, NULL);
	if (argv[5])
		values->args.nmeals = (int)ft_atoi(argv[5]);
	i = -1;
	while (++i < values->args.nphilos)
	{
		pthread_mutex_init(&values->forks[i], NULL);
		pthread_mutex_init(&values->philos[i].is_dying, NULL);
		pthread_mutex_init(&values->philos[i].eating, NULL);
		values->philos[i].meals = values->args.nmeals;
		values->philos[i].n = i + 1;
		values->philos[i].values = values;
	}
}

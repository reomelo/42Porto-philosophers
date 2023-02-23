/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:21:08 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/23 18:41:00 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meals_left(t_values *values)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&values->is_dead);
	while (++i < values->args.nphilos)
	{
		if (values->philos[i].meals > 0)
		{
			pthread_mutex_unlock(&values->is_dead);
			return (1);
		}
	}
	pthread_mutex_unlock(&values->is_dead);
	return (0);
}

void	joining_threads(t_values *values)
{
	int	i;

	i = -1;
	while (++i < values->args.nphilos && !values->deaths)
		pthread_join(values->philos[i].id, NULL);
}

void	*lets_eat(void *data)
{
	t_philos	*philos;

	philos = (t_philos *)data;
	if (!(philos->n % 2))
		usleep(2000);
	while (1)
	{
		pthread_mutex_lock(&philos->values->is_dead);
		if (philos->values->deaths || philos->values->finished)
		{
			pthread_mutex_unlock(&philos->values->is_dead);
			break ;
		}
		pthread_mutex_unlock(&philos->values->is_dead);
		if (!forking(philos))
			break ;
		eating(philos);
		sleeping(philos);
		thinking(philos);
	}
	return (NULL);
}

void	waiter(t_values *values)
{
	int	i;
	int	count;
	
	i = -1;
	while (!values->deaths)
	{
		i = -1;
		count = 0;
		while (++i < values->args.nphilos)
		{
			if (died(&values->philos[i], &count))
				break ;
		}
		if (count >= values->args.nphilos)
		{
			pthread_mutex_lock(&values->is_dead);
			values->finished = true;
			pthread_mutex_unlock(&values->is_dead);
			break ;
		}
	}
}

int	main(int argc, char *argv[])
{
	int			i;
	t_values	*values;

	values = malloc(sizeof(t_values));
	if (errors(argc, argv))
	{
		free_all_stacks(values, 'e');
		return (1);
	}
	else
	{
		initiate(argv, values);
		i = -1;
		if (argc == 6 && !values->args.nmeals)
			free_all_stacks(values, 'f');
		values->start_time = get_time();
		while (++i < values->args.nphilos)
		{
			values->philos[i].last_meal = get_time();
			pthread_create(&values->philos[i].id, NULL, lets_eat, &values->philos[i]);
		}
		waiter(values);
		joining_threads(values);
	}
	free_all_stacks(values, 'f');
	return (0);
}

//ALIVE: clear && make fclean && make && ./philo 2 500 200 100 1
//DIES: clear && make fclean && make && ./philo 3 310 200 100 1
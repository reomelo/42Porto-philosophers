/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:21:08 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/21 23:46:55 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meals_left(t_values *values)
{
	int	i;

	i = -1;
	while (++i < values->args.nphilos)
		if (values->philos[i].meals > 0)
			return (1);
	return (0);
}

void	joining_threads(t_values *values)
{
	int	i;

	i = -1;
	while (++i < values->args.nphilos)
		pthread_join(values->philos[i].id, NULL);
}

void	*lets_eat(void *data)
{
	t_philos	*philos;

	philos = (t_philos *)data;
	if (!(philos->n % 2))
		usleep(200);
	while (!philos->values->deaths && meals_left(philos->values))
	{
		if (!forking(philos))
		{
			philos->values->print = false;
			break ;
		}
		eating(philos);
		sleeping(philos);
		thinking(philos);
	}
	return (NULL);
}

void	waiter(t_values *values)
{
	int			i;
	int			count;
	
	count = 0;
	while (!values->deaths)
	{
		i = -1;
		while (++i < values->args.nphilos)
		{
			if (died(values->philos[i]))
				break ;
		}
		if (!meals_left(values))
			break ;
	}
	return (NULL);
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
			if (!pthread_create(&values->philos[i].id, NULL,
				lets_eat, &values->philos[i]))
				pthread_detach(values->philos[i].id);
		}
		waiter(&values);
		/* joining_threads(values); */
	}
	free_all_stacks(values, 'f');
	return (0);
}

//ALIVE: clear && make fclean && make && ./philo 2 500 200 100 1
//DIES: clear && make fclean && make && ./philo 3 310 200 100 1
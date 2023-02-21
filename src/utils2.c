/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:29:46 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/21 18:57:35 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	died(t_philos *philos)
{
	if (get_time() - philos->last_meal >= philos->values->args.tdie)
	{
		values->deaths = true;
		dying(philos);
		return (1);
	}
	return (0);
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

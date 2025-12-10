/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:38:15 by phofer            #+#    #+#             */
/*   Updated: 2025/12/10 17:39:27 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	parse_args(char **av, t_rules	*rules)
{
	int	i;
	int	temp;

	i = 1;
	rules->eat_amount = -1;
	while (av[i])
	{
		temp = ft_atoi(av[i]);
		if ((temp > 0) && temp < MAX_INPUT)
		{
			if (i == 1)
				rules->quantity = temp;
			else if (i == 2)
				rules->time_to_die = temp;
			else if (i == 3)
				rules->time_to_eat = temp;
			else if (i == 4)
				rules->time_to_sleep = temp;
			else if (i == 5)
				rules->eat_amount = temp;
		}
		else
			exit (printf("Error input %d: Only numbers > 0 are accepted\n", i));
		++i;
	}
}

int	init_forks(t_rules	*rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->quantity);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->quantity)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&rules->forks[i]);
			free(rules->forks);
			rules->forks = NULL;
			return (1);
		}
		++i;
	}
	return (0);
}

int	init_mutex(t_rules *rules)
{
	if (pthread_mutex_init(&rules->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&rules->meal_check, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->write_lock);
		return (1);
	}
	return (0);
}

int	init_philosophers(t_rules *rules)
{
	int	i;

	rules->philos = malloc(sizeof(t_philo) * rules->quantity);
	if (!rules->philos)
		return (1);
	i = 0;
	while (i < rules->quantity)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].left_fork = i;
		rules->philos[i].right_fork = (i + 1) % rules->quantity;
		rules->philos[i].last_meal = 0;
		rules->philos[i].eat_count = 0;
		rules->philos[i].rules = rules;
		i++;
	}
	return (0);
}

void	initialize(char **av, t_rules	*rules)
{
	init_philo(av, rules);
	if (init_forks(&rules) != 0)
	{
		printf("ERROR: init_mutex failed");
		exit (1);
	}
	if (init_mutex(&rules) != 0)
	{
		printf("ERROR: init_mutex failed");
		free_all(&rules);
		exit (1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:38:15 by phofer            #+#    #+#             */
/*   Updated: 2025/12/16 15:55:35 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(char **av, t_rules	*rules)
{
	int	i;
	int	temp;

	i = 1;
	while (av[i])
	{
		temp = ft_atoi_strict(av[i]);
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
			return (1);
		++i;
	}
	return (0);
}

int	init_args(char **av, t_rules	*rules)
{
	rules->eat_amount = -1;
	if (parse_args(av, rules) != 0)
	{
		printf("Error: Only numbers > 0 are accepted\n");
		return (1);
	}
	rules->stop = 0;
	rules->start_time = 0;
	rules->dead = 0;
	rules->all_full = 0;
	rules->total_finished = 0;
	rules->philos = NULL;
	rules->forks = NULL;
	rules->start_time = ft_now_ms();
	if (!rules->start_time)
	{
		printf("ERROR: gettimeofday failed");
		return (1);
	}
	return (0);
}

int	init_philosophers(t_rules *rules)
{
	int	i;
	int	n;

	n = rules->quantity;
	rules->philos = malloc(sizeof(t_philo) * n);
	if (!rules->philos)
		return (1);
	i = 0;
	while (i < n)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(i + 1) % n];
		rules->philos[i].last_meal = rules->start_time;
		rules->philos[i].eat_count = 0;
		rules->philos[i].rules = rules;
		i++;
	}
	return (0);
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
			return (1);
		++i;
	}
	if (pthread_mutex_init(&rules->state_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&rules->write_lock, NULL) != 0)
		return (1);
	return (0);
}

void	initialize(char **av, t_rules	*rules)
{
	if (init_args(av, rules) != 0)
		exit (1);
	if (init_forks(rules) != 0)
	{
		printf("ERROR: init_forks failed");
		free_all(rules);
		exit (1);
	}
	if (init_philosophers(rules) != 0)
	{
		printf("ERROR: init_philosophers failed");
		free_all(rules);
		exit (1);
	}

}


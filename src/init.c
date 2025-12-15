/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:38:15 by phofer            #+#    #+#             */
/*   Updated: 2025/12/15 16:57:36 by phofer           ###   ########.fr       */
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
			exit (printf("Error input %d: Only numbers > 0 are accepted\n", i));
		++i;
	}
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
		pthread_mutex_init(&rules->philos[i].left_fork, NULL);
		if (i + 1 == rules->quantity)
			rules->philos[i].right_fork = &rules->philos[0].left_fork;
		else
			rules->philos[i].right_fork = &rules->philos[i + 1].left_fork;
		rules->philos[i].last_meal = rules->start_time;
		rules->philos[i].eat_count = 0;
		rules->philos[i].rules = rules;
		i++;
	}
	return (0);
}

void	init_args(char **av, t_rules	*rules)
{
	parse_args(av, rules);
	pthread_mutex_init(&rules->write_lock, NULL);
	rules->stop = 0;
	rules->start_time = 0;
	rules->philos = NULL;
}

void	initialize(char **av, t_rules	*rules)
{
	init_args(av, rules);
	rules->start_time = ft_now_ms();
	if (!rules->start_time)
	{
		printf("ERROR: gettimeofday failed");
		// free_all(&rules);
		exit (1);
	}
	if (init_philosophers(rules) != 0)
	{
		printf("ERROR: init_philosophers failed");
		// free_all(&rules);
		exit (1);
	}
}


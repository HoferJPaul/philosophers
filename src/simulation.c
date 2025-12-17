/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:48:58 by phofer            #+#    #+#             */
/*   Updated: 2025/12/17 18:11:54 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->quantity)
	{
		if (pthread_create(&rules->philos[i].thread, NULL,
				t_philo_routine, &rules->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	join_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->quantity)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
}

static int	check_death(t_rules *rules)
{
	int			i;
	uint64_t	now;
	uint64_t	last;
	uint64_t	time_since_meal;

	i = 0;
	while (i < rules->quantity)
	{
		now = ft_now_ms();
		pthread_mutex_lock(&rules->state_lock);
		last = rules->philos[i].last_meal;
		time_since_meal = now - last;
		if (time_since_meal > (uint64_t)rules->time_to_die)
		{
			rules->stop = 1;
			pthread_mutex_unlock(&rules->state_lock);
			print_death(&rules->philos[i]);
			return (1);
		}
		pthread_mutex_unlock(&rules->state_lock);
		i++;
	}
	return (0);
}

void	monitor_simulation(t_rules *rules)
{
	while (!get_stop(rules))
	{
		if (check_death(rules))
			return ;
		if (check_all_full(rules))
		{
			set_stop(rules, 1);
			return ;
		}
		usleep(1000);
	}
}

int	run_simulation(t_rules *rules)
{
	int	i;

	pthread_mutex_lock(&rules->state_lock);
	rules->start_time = ft_now_ms();
	i = 0;
	while (i < rules->quantity)
	{
		rules->philos[i].last_meal = rules->start_time;
		i++;
	}
	pthread_mutex_unlock(&rules->state_lock);
	if (start_threads(rules) != 0)
	{
		set_stop(rules, 1);
		join_threads(rules);
		return (1);
	}
	monitor_simulation(rules);
	join_threads(rules);
	return (0);
}

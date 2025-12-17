/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:50:50 by phofer            #+#    #+#             */
/*   Updated: 2025/12/17 17:46:12 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep_ms(t_rules *r, int ms)
{
	uint64_t	end;

	end = ft_now_ms() + (uint64_t)ms;
	while (!get_stop(r) && ft_now_ms() < end)
		usleep(500);
}

int	check_all_full(t_rules *rules)
{
	int	i;
	int	full;

	if (rules->eat_amount == -1)
		return (0);
	full = 0;
	i = 0;
	while (i < rules->quantity)
	{
		if (get_eat_count(&rules->philos[i]) >= rules->eat_amount)
			full++;
		i++;
	}
	return (full == rules->quantity);
}

uint64_t	get_last_meal(t_philo *p)
{
	uint64_t	t;

	pthread_mutex_lock(&p->rules->state_lock);
	t = p->last_meal;
	pthread_mutex_unlock(&p->rules->state_lock);
	return (t);
}

void	inc_eat_count(t_philo *p)
{
	pthread_mutex_lock(&p->rules->state_lock);
	p->eat_count++;
	pthread_mutex_unlock(&p->rules->state_lock);
}

int	get_eat_count(t_philo *p)
{
	int	n;

	pthread_mutex_lock(&p->rules->state_lock);
	n = p->eat_count;
	pthread_mutex_unlock(&p->rules->state_lock);
	return (n);
}

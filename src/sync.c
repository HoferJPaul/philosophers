/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:51:39 by phofer            #+#    #+#             */
/*   Updated: 2025/12/17 17:48:59 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_stop(t_rules *r)
{
	int	stop;

	pthread_mutex_lock(&r->state_lock);
	stop = r->stop;
	pthread_mutex_unlock(&r->state_lock);
	return (stop);
}

void	set_stop(t_rules *r, int value)
{
	pthread_mutex_lock(&r->state_lock);
	r->stop = value;
	pthread_mutex_unlock(&r->state_lock);
}

void	print_state(t_philo *p, const char *msg)
{
	uint64_t	ts;

	pthread_mutex_lock(&p->rules->write_lock);
	if (!get_stop(p->rules))
	{
		ts = ft_now_ms() - p->rules->start_time;
		printf("%llu %d %s\n", (unsigned long long)ts, p->id, msg);
	}
	pthread_mutex_unlock(&p->rules->write_lock);
}

void	print_death(t_philo *p)
{
	uint64_t	ts;

	pthread_mutex_lock(&p->rules->write_lock);
	ts = ft_now_ms() - p->rules->start_time;
	printf("%llu %d died\n", (unsigned long long)ts, p->id);
	pthread_mutex_unlock(&p->rules->write_lock);
}

void	set_last_meal(t_philo *p, uint64_t t)
{
	pthread_mutex_lock(&p->rules->state_lock);
	p->last_meal = t;
	pthread_mutex_unlock(&p->rules->state_lock);
}

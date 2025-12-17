/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:44:15 by phofer            #+#    #+#             */
/*   Updated: 2025/12/17 17:48:13 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *p)
{
	if (p->rules->quantity == 1)
	{
		pthread_mutex_lock(p->left_fork);
		print_state(p, "has taken a fork");
		return ;
	}
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->right_fork);
		print_state(p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);
		print_state(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->left_fork);
		print_state(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		print_state(p, "has taken a fork");
	}
}

static void	put_forks(t_philo *p)
{
	if (p->rules->quantity == 1)
	{
		pthread_mutex_unlock(p->left_fork);
		return ;
	}
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

static void	eat_action(t_philo *p)
{
	set_last_meal(p, ft_now_ms());
	print_state(p, "is eating");
	ft_sleep_ms(p->rules, p->rules->time_to_eat);
	inc_eat_count(p);
}

static int	handle_one_philo(t_philo *p)
{
	if (p->rules->quantity != 1)
		return (0);
	take_forks(p);
	while (!get_stop(p->rules))
		usleep(500);
	put_forks(p);
	return (1);
}

void	*t_philo_routine(void *arg)
{
	t_philo	*p;
	int		no_fair;

	p = (t_philo *)arg;
	no_fair = (p->rules->quantity >= 31
			&& p->rules->time_to_die < (p->rules->time_to_eat * 3));
	if (p->id % 2 == 0 && !no_fair)
		usleep((p->rules->quantity <= 10)
			* (p->rules->time_to_eat / 2) * 1000
			+ (p->rules->quantity > 10) * 1000);
	while (!get_stop(p->rules))
	{
		if (handle_one_philo(p))
			break ;
		take_forks(p);
		eat_action(p);
		put_forks(p);
		print_state(p, "is sleeping");
		ft_sleep_ms(p->rules, p->rules->time_to_sleep);
		print_state(p, "is thinking");
		if (!no_fair && p->rules->quantity <= 10
			&& (p->rules->quantity % 2 == 1))
			usleep(1000);
	}
	return (NULL);
}

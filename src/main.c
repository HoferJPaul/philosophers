/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:15:43 by phofer            #+#    #+#             */
/*   Updated: 2025/12/17 17:46:28 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_rules *rules)
{
	int	i;

	if (!rules)
		return ;
	if (rules->forks)
	{
		i = 0;
		while (i < rules->fork_flag)
		{
			pthread_mutex_destroy(&rules->forks[i]);
			i++;
		}
		free(rules->forks);
		rules->forks = NULL;
	}
	if (rules->state_flag == 1)
		pthread_mutex_destroy(&rules->state_lock);
	if (rules->write_flag == 1)
		pthread_mutex_destroy(&rules->write_lock);
	if (rules->philos)
	{
		free(rules->philos);
		rules->philos = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	memset(&rules, 0, sizeof(t_rules));
	if (argc < 5 || argc > 6)
	{
		printf("./rules 'quantity time2die time2eat time2sleep number2eat'\n");
		return (1);
	}
	initialize(argv, &rules);
	run_simulation(&rules);
	free_all(&rules);
	return (0);
}

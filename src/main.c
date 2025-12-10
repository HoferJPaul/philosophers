/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:15:43 by phofer            #+#    #+#             */
/*   Updated: 2025/12/10 18:18:40 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_rules *rules)
{

}

void	init_philo(char **av, t_rules	*rules)
{
	parse_args(av, rules);
	rules->stop = 0;
	rules->start_time = 0;
	rules->forks = NULL;
	rules->philos = NULL;
}

//test function, dont include in final
void	print_struct(t_rules	*rules)
{
	printf("quantity = %d\n", rules->quantity);
	printf("time_to_die = %d\n", rules->time_to_die);
	printf("time_to_eat = %d\n", rules->time_to_eat);
	printf("time_to_sleep = %d\n", rules->time_to_sleep);
	printf("eat_amount = %d\n", rules->eat_amount);
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
	print_struct(&rules);
	return (0);
}

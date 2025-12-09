/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:15:43 by phofer            #+#    #+#             */
/*   Updated: 2025/12/09 16:39:56 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	parse_args(char **av, t_args	*philo)
{
	int	i;
	int	temp;

	i = 1;
	philo->eat_amount = -1;
	while (av[i])
	{
		temp = ft_atoi(av[i]);
		if ((temp > 0) && temp < MAX_INPUT)
		{
			if (i == 1)
				philo->quantity = temp;
			else if (i == 2)
				philo->time_to_die = temp;
			else if (i == 3)
				philo->time_to_eat = temp;
			else if (i == 4)
				philo->time_to_sleep = temp;
			else if (i == 5)
				philo->eat_amount = temp;
		}
		else
			exit (printf("Error %d: Only numbers above 0 are accepted\n", i));
		++i;
	}
}

void	print_struct(t_args	*philo)
{
	printf("quantity = %d\n", philo->quantity);
	printf("time_to_die = %d\n", philo->time_to_die);
	printf("time_to_eat = %d\n", philo->time_to_eat);
	printf("time_to_sleep = %d\n", philo->time_to_sleep);
	printf("eat_amount = %d\n", philo->eat_amount);
}

int	main(int argc, char **argv)
{
	t_args	philo;

	memset(&philo, 0, sizeof(t_args));
	if (argc < 5 || argc > 6)
	{
		printf("./philo quantity time2die time2eat time2sleep number_of_eat\n");
		return (1);
	}
	parse_args(argv, &philo);

	print_struct(&philo);
	return (0);
}

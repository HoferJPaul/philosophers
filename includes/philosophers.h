/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:33:51 by phofer            #+#    #+#             */
/*   Updated: 2025/12/10 17:40:37 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_INPUT 1000

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int id;         // Philosopher number (1..n)
	int left_fork;  // Index of left fork mutex
	int right_fork; // Index of right fork mutex

	long last_meal; // Timestamp of last meal (ms)
	int eat_count;  // How many times this philosopher has eaten

	pthread_t thread;      // Thread representing this philosopher
	struct s_rules *rules; // Pointer to the shared simulation rules
}		t_philo;

typedef struct s_rules
{
	int	quantity;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	eat_amount;

	int stop;        // flag: 1 = simulation should end
	long start_time; // timestamp when simulation starts

	pthread_mutex_t *forks;     // array of fork mutexes (size = n_philos)
	pthread_mutex_t write_lock; // protects printing
	pthread_mutex_t meal_check; // protects last_meal & eat_count updates
	t_philo *philos;            // pointer to array of all philosophers
}		t_rules;

int		ft_atoi(const char *str);
void	initialize(char **av, t_rules	*rules);
void	init_philo(char **av, t_rules	*rules);

#endif

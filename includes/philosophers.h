/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:33:51 by phofer            #+#    #+#             */
/*   Updated: 2025/12/16 15:53:54 by phofer           ###   ########.fr       */
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
	uint64_t last_meal; // Timestamp of last meal (ms)
	int eat_count;  // How many times this philosopher has eaten

	pthread_mutex_t *left_fork;  // pointer to left fork mutex
	pthread_mutex_t *right_fork; // pointer to right fork mutex
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
	int	total_finished;
	int	dead;
	int	all_full;

	int			stop;		// flag: 1 = simulation should end
	uint64_t	start_time; // timestamp when simulation starts

	pthread_mutex_t *forks;
	pthread_mutex_t write_lock; // protects printing
	pthread_mutex_t state_lock;
	t_philo *philos;            // pointer to array of all philosophers
}		t_rules;

enum e_fork
{
	LEFT,
	RIGHT
};

int			ft_atoi_strict(const char *str);
uint64_t	ft_now_ms(void);
void		initialize(char **av, t_rules	*rules);
int			init_args(char **av, t_rules	*rules);
int			parse_args(char **av, t_rules	*rules);
void		free_all(t_rules *rules);

#endif

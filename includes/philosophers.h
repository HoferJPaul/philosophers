/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:33:51 by phofer            #+#    #+#             */
/*   Updated: 2025/12/17 17:53:04 by phofer           ###   ########.fr       */
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
	int				id;
	uint64_t		last_meal;
	int				eat_count;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_rules	*rules;
}		t_philo;

typedef struct s_rules
{
	int				quantity;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				eat_amount;
	int				total_finished;
	int				dead;
	int				all_full;

	int				stop;
	uint64_t		start_time;

	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	state_lock;

	int				fork_flag;
	int				write_flag;
	int				state_flag;
	t_philo			*philos;
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
void		*t_philo_routine(void *arg);
int			run_simulation(t_rules *rules);
int			check_all_full(t_rules *rules);
uint64_t	get_last_meal(t_philo *p);
void		inc_eat_count(t_philo *p);
int			get_eat_count(t_philo *p);
void		set_last_meal(t_philo *p, uint64_t t);
void		print_death(t_philo *p);
void		print_state(t_philo *p, const char *msg);
void		set_stop(t_rules *r, int value);
int			get_stop(t_rules *r);
void		ft_sleep_ms(t_rules *r, int ms);

#endif

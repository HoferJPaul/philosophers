/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:33:51 by phofer            #+#    #+#             */
/*   Updated: 2025/12/09 16:35:48 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_INPUT 1000

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_args
{
	int	quantity;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	eat_amount;

}	t_args;

int	ft_atoi(const char *str);

#endif

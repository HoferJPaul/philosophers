/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:01:39 by phofer            #+#    #+#             */
/*   Updated: 2025/12/09 16:09:34 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long int	result;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result < 0)
			return ((sign != -1) * -1);
		++i;
	}
	return (result * sign);
}

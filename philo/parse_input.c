/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:09:14 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/21 23:09:16 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Parse Input
 * @brief Parses the input arguments and stores them in the table.
 *
 * @param table A pointer to the table structure.
 * @param av The input arguments.
 *                            av[1] av[2] av[3] av[4]  av[5]
 * Ex. of Execution: ./ philo 5     800   200   200    [5]
 */

/*
 * 1. Check if the number of philosophers is an actual number.
 *     - They can't be negative.
 * 2. It can't be over INT_MAX.
 *     - How to check if it's over INT_MAX?
 *         - If the number is over 10 digits, it's over INT_MAX.
 * 3. The Timestamps must be over 60ms.
 */
static long		ft_atol(const char *str);
static size_t	ft_strlen(const char *str);

static long	ft_atol(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	if (ft_strlen(str) > 10 || str == "2147483647")
		return (-1);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	if (res > 2147483647)
		return (-1);
	return (res * sign);
}

static size_t	ft_strlen(const char *str)
{
	size_t i;

	i = -1;
	while (str[++i])
		continue ;
	return (i);
}
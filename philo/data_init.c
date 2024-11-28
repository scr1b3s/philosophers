/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrde-s <andrde-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:20:29 by k-maru            #+#    #+#             */
/*   Updated: 2024/11/27 21:26:30 by andrde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_number;

	philo_number = philo->table->num_philos;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_number];
	}
	else
	{
		philo->first_fork = &forks[(position + 1) % philo_number];
		philo->second_fork = &forks[position];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mtx, INIT);
		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	if (table->num_philos < 1)
	{
		printf("Error: Invalid number of philosophers.\n");
		table->end_simulation = true;
		table->philos = NULL;
		table->forks = NULL;
		exit(1);
	}
	else
	{
		table->end_simulation = false;
		table->all_philos_ready = false;
		table->philos_ready = 0;
		safe_mutex_handle(&table->table_mtx, INIT);
		safe_mutex_handle(&table->write_mtx, INIT);
		table->philos = safe_malloc(sizeof(t_philo) * table->num_philos);
		table->forks = safe_malloc(sizeof(t_fork) * table->num_philos);
		i = -1;
		while (++i < table->num_philos)
		{
			safe_mutex_handle(&table->forks[i].fork, INIT);
			table->forks[i].fork_id = i;
		}
		philo_init(table);
	}
}

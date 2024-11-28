/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrde-s <andrde-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:11:41 by k-maru            #+#    #+#             */
/*   Updated: 2024/11/27 21:26:52 by andrde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    desynch_philo(t_philo *philo)
{
    if (philo->table->num_philos % 2 == 0)
    {
        if (philo->id % 2 == 0)
            precise_usleep(3e4, philo->table);
    }
    else
    {
        if (philo->id % 2 != 0)
            think(philo);
    }
}

void    cleaning_table(t_table *table)
{
    t_philo *philo;
    int i;

    i = -1;
    while (++i < table->num_philos)
    {
        philo = table->philos + i;
        safe_mutex_handle(&philo->philo_mtx, DESTROY);
    }
    safe_mutex_handle(&table->write_mtx, DESTROY);
    safe_mutex_handle(&table->table_mtx, DESTROY);
    free(table->philos);
    free(table->forks);
}
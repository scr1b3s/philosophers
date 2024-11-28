/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrde-s <andrde-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:27:17 by k-maru            #+#    #+#             */
/*   Updated: 2024/11/27 21:26:36 by andrde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo)
{
    long    duration;
    long    t_to_die;

    if (get_bool(&philo->philo_mtx, &philo->full))
        return (false);

    duration = get_time(MILLISECOND) - get_long(&philo->philo_mtx, &philo->last_meal_time);
    t_to_die = philo->table->time_to_die / 1e3;

    if (duration > t_to_die)
        return (true);
    return (false);
}

void    *monitor_dinner(void *data)
{
    t_table *table;
    int     i;

    table = (t_table *)data;
    i = -1;

    while (!all_threads_running(&table->table_mtx, &table->philos_ready, table->num_philos))
        continue ;

    while (!simulation_finisihed(table))
    {
        i = -1;
        while (++i < table->num_philos && !simulation_finisihed(table))
        {
            if (philo_died(table->philos + i))
            {
                write_status(DEAD, table->philos + i, DEBUG_MODE);
                set_bool(&table->table_mtx, &table->end_simulation, true);
            }
        }
    }
    return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrde-s <andrde-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:23:11 by k-maru            #+#    #+#             */
/*   Updated: 2024/11/27 21:26:54 by andrde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static  void write_debug_status(t_philo_status status, t_philo *philo, long time);

/*
 * [time_ms] [philo_id] [action]
 */

void    write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long    time;

    time = get_time(MILLISECOND) - philo->table->start_time;

    if (philo->full)
        return ;

    safe_mutex_handle(&philo->table->write_mtx, LOCK);
    if (debug)
        write_debug_status(status, philo, time);
    else
    {
        if ((status == FIRST_FORK || status == SECOND_FORK)
        && !simulation_finisihed(philo->table))
            printf("%-6ld %d has taken a fork\n",
            time, philo->id);
        else if (status == EATING
        && !simulation_finisihed(philo->table))
            printf("%-6ld %d is eating\n", time, philo->id);
        else if (status == SLEEPING
        && !simulation_finisihed(philo->table))
            printf("%-6ld %d is sleeping\n", time, philo->id);
        else if (status == THINKING
        && !simulation_finisihed(philo->table))
            printf("%-6ld %d is thinking\n", time, philo->id);
        else if (status == DEAD
        && !simulation_finisihed(philo->table))
            printf("%-6ld %d died\n", time, philo->id);
    }
    safe_mutex_handle(&philo->table->write_mtx, UNLOCK);
}

static  void write_debug_status(t_philo_status status, t_philo *philo, long time)
{
    if (status == FIRST_FORK
    && !simulation_finisihed(philo->table))
        printf("%-6ld %d had taken the first fork\n", time, philo->id);
    else if (status == SECOND_FORK
    && !simulation_finisihed(philo->table))
        printf("%-6ld %d had taken the second fork\n", time, philo->id);
    else if (status == EATING
    && !simulation_finisihed(philo->table))
        printf("%-6ld %d is eating, has eaten %ld times.\n",
        time, philo->id, philo->meals_count);
    else if (status == SLEEPING
    && !simulation_finisihed(philo->table))
        printf("%-6ld %d is sleeping\n", time, philo->id);
    else if (status == THINKING
    && !simulation_finisihed(philo->table))
        printf("%-6ld %d is thinking\n", time, philo->id);
    else if (status == DEAD
    && simulation_finisihed(philo->table))
        printf("%-6ld %d died\n", time, philo->id);
}
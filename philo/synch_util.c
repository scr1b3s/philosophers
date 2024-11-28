/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synch_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrde-s <andrde-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:31:56 by k-maru            #+#    #+#             */
/*   Updated: 2024/11/27 21:26:50 by andrde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Wait All Threads
 * @brief Function that waits for all threads to be ready.
 *
 * This function waits for all threads
 * to be ready before starting the simulation.
 * It's a basic spinlock synchronization mechanism.
 *
 * @param table A pointer to the table structure.
 */
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_philos_ready))
		continue ;
}

bool    all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
    bool   threads_ready;
    
    threads_ready = false;
    safe_mutex_handle(mtx, LOCK);
    if (*threads == philo_nbr)
        threads_ready = true;
    safe_mutex_handle(mtx, UNLOCK);

    return (threads_ready);
}

void    add_long(t_mtx *mtx, long *var)
{
    safe_mutex_handle(mtx, LOCK);
    *var += 1;
    safe_mutex_handle(mtx, UNLOCK);
}

long    get_time(t_time_code time_code)
{
    struct timeval  time;

    if (gettimeofday(&time, NULL))
    {
        printf("Error: gettimeofday failed.\n");
        exit(1);
    }
    if (time_code == SECOND)
        return (time.tv_sec + (time.tv_usec / 1e6));
    else if (time_code == MILLISECOND)
        return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
    else if (time_code == MICROSECOND)
        return (time.tv_sec * 1e6 + time.tv_usec);
    else
    {
        printf("Error: Invalid time code.\n");
        exit(1);
    }

    return (42);
}

void    precise_usleep(long usec, t_table *table)
{
    long    start_time;
    long    passed;
    long    current_time;
    long    remaining;

    start_time = get_time(MICROSECOND);
    while (get_time(MICROSECOND) - start_time < usec)
    {
        if (simulation_finisihed(table))
            break ;

        passed = get_time(MICROSECOND) - start_time;
        remaining = usec - passed;

        if (remaining > 1e3)
            usleep(remaining / 2);
        else
        {
            while (get_time(MICROSECOND) - start_time < usec)
                continue ;
        }
    }
}
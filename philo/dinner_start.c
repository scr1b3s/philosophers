/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:25:44 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/28 19:25:45 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

/*
 * Dinner Simulation
 * 00: Needs to wait the philos, synch starts.
 * 01: Endless loop.
 */

// TODO: Play w/ thinking.
static void think(t_philo *philo)
{
    write_status(THINKING, philo, DEBUG_MODE);
}

static void eat(t_philo *philo)
{
    // STARTS TO EAT:
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(FIRST_FORK, philo, DEBUG_MODE);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(SECOND_FORK, philo, DEBUG_MODE);

    // EATING:
    set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECOND));
    philo->meals_count++;
    write_status(EATING, philo, DEBUG_MODE);
    precise_usleep(philo->table->time_to_eat, philo->table);

    if (philo->table->num_meals > 0
    && philo->meals_count == philo->table->num_meals)
            set_bool(&philo->philo_mtx, &philo->full, true);
    
    // FINISHED EATING:
    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->table);

    // Last meal time.
    while (!simulation_finisihed(philo->table))
    {
        // Check if full.
        if (philo->full) // Needs to check if thread safe.
            break ;
        
        // TODO:
        // Write Status && Usleep is shit ==> PRECISE_USLEEP
        eat(philo);
        
        // SLEEP:
        write_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->table->time_to_sleep, philo->table);
        
        think(philo);
    }
    return (NULL);
}

/* STUFF TO DO:
 * 
 * 00: If no meals, return.
 * 01: If one philo only: ad hoc func.
 * 02: Creates all the Threads and Philos.
 * 03: Synch start of simulation.
 *      -- pthread_create --> All philo start.
 *          They indeed must start at the same time.
 * 
 * 04: Join all Philosophers.
 */

void    dinner_start(t_table *table)
{
    // 
    int i;

    i = -1;
    if (table->num_meals == 0)
        return ;
    else if (table->num_philos == 1)
    {
        // TODO: One Philosopher Only.
    }
    else
    {
        while (++i < table->num_philos)
            // TODO: Dinner Simulation.
            safe_thread_handle(&table->philos[i].thread_id,
            dinner_simulation,
            &table->philos[i],
            CREATE);
    }

    // Start the simulation.
    table->start_time = get_time(MILLISECOND);

    // All Threads are ready!
    set_bool(&table->table_mtx, &table->all_philos_ready, true);

    // Wait for all threads to finish.
    i = -1;
    while (++i < table->num_philos)
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);

    dinner_simulation(table->philos);
}
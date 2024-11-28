/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrde-s <andrde-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:20:35 by k-maru            #+#    #+#             */
/*   Updated: 2024/11/27 21:27:04 by andrde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

/*
 * Dinner Simulation
 * 00: Needs to wait the philos, synch starts.
 * 01: Endless loop.
 */

// TODO: Play w/ thinking.
void think(t_philo *philo)
{
    long    t_eat;
    long    t_sleep;
    long    t_think;

    write_status(THINKING, philo, DEBUG_MODE);

    if (philo->table->num_philos % 2 == 0)
        return ;

    t_eat = philo->table->time_to_eat;
    t_sleep = philo->table->time_to_sleep;
    t_think = t_eat * 2 - t_sleep;

    if (t_think < 0)
        t_think = 0;
    
    precise_usleep(t_think * 0.42, philo->table);

}

void    *lone_philo(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->table);

    set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECOND));

    add_long(&philo->table->table_mtx, &philo->table->philos_ready);

    write_status(FIRST_FORK, philo, DEBUG_MODE);
    
    while (!simulation_finisihed(philo->table))
        usleep(200);

    return (NULL);
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

    set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECOND));

    add_long(&philo->table->table_mtx, &philo->table->philos_ready);

    desynch_philo(philo);

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
        safe_thread_handle(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE);
    else
    {
        while (++i < table->num_philos)
            safe_thread_handle(&table->philos[i].thread_id,
            dinner_simulation,
            &table->philos[i],
            CREATE);
    }

    // Monitoring the Philosophers
    safe_thread_handle(&table->monitor_thread, monitor_dinner, table, CREATE);

    // Start the simulation.
    table->start_time = get_time(MILLISECOND);

    // All Threads are ready!
    set_bool(&table->table_mtx, &table->all_philos_ready, true);

    // Wait for all threads to finish.
    i = -1;
    while (++i < table->num_philos)
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);

    set_bool(&table->table_mtx, &table->end_simulation, true);
    safe_thread_handle(&table->monitor_thread, NULL, NULL, JOIN);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:17:42 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/21 01:17:44 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

/* We use the main as a TL;DR of the program... From here, we can see the
 * necessary implementations for the program to run properly.
 * 
 * Ex. of Execution: ./ philo 5 800 200 200 [5]
 */

int	main(int ac, char **av)
{
    t_table table;
    
    // We check if the number of arguments is correct.
    if (ac == 5 || ac == 6)
    {
        // We parse the input arguments and store them in the table.
        parse_input(&table, ac, av);

        // TODO: Initialize the table.
        data_init(&table);

        // // TODO: Start the simulation.
        dinner_start(&table);

        // // TODO: Clean up the table. -> Philos Full or 1 Philo Died.
        // cleaning_time(&table);
    }
    else
    {
        // Incorrect number of args.
        // Print the usage of the program.
        printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [num_meals]\n");
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
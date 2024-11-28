/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrde-s <andrde-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:17:42 by k-maru            #+#    #+#             */
/*   Updated: 2024/11/27 21:26:35 by andrde-s         ###   ########.fr       */
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
    
    if (ac == 5 || ac == 6)
    {
        parse_input(&table, ac, av);

        data_init(&table);

        dinner_start(&table);

        cleaning_table(&table);
    }
    else
    {
        printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [num_meals]\n");
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
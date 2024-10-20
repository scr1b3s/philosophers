/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coffee_thread_mutex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:39:57 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/20 16:39:59 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>

/* Aqui, nós vamos trabalhar com mutexes. Garantindo que apenas um barista 
 * possa fazer café por vez. Introduzindo o conceito de Sincronização.
 */

#define TH 1000

// Recurso Compartilhado 📝
uint64_t coffee_made = 0;

static void    *make_coffee(void *data)
{
    (void)data;
    // Realização do Café:
    coffee_made += 1;

    return (NULL);
}

int main(int ac, char **av)
{
    uint64_t        thread_num = av[1] ? atoi(av[1]) : TH;
    uint64_t        i = 0;
    pthread_t       baristas[thread_num];

    (void )ac;
    while (i < thread_num)
    {
        if (pthread_create(&baristas[i], NULL, make_coffee, NULL))
            return (EXIT_FAILURE);
        i++;
    }

    i = 0;
    while (i < thread_num)
    {
        pthread_join(baristas[i], NULL);
        i++;
    }

    printf("Coffee's made: %ld.\n", coffee_made);

    return (EXIT_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coffee_thread_mutex_solve.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:06:05 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/20 17:06:08 by k-maru           ###   ########.fr       */
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

// Mutex utilizado p/ Trancar & Destrancar 🔒
pthread_mutex_t lock_coffee = PTHREAD_MUTEX_INITIALIZER;

static void    *make_coffee(void *data)
{
    (void)data;
    
    /* Trancando a Nota do Café 🔒 */
    pthread_mutex_lock(&lock_coffee);
    coffee_made += 1;
    //printf("Did %ld Coffees.\n", coffee_made);
    /* Destrancando a Nota 🔓 */
    pthread_mutex_unlock(&lock_coffee);

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

    printf("Coffees made: %ld.\n", coffee_made);

    return (EXIT_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadlock_intro.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:36:15 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/20 17:36:16 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Vamos começar a trabalhar com o conceito de Deadlocks. Deadlocks são situações
 * em que dois ou mais processos ficam esperando indefinidamente por um recurso
 * que nunca será liberado.
 * 
 * A metáfora que utilizaremos é a de um Stand-Off, onde dois processos estão
 * apontando armas um para o outro, e ambos estão esperando o outro atirar para
 * poderem atirar também...
 */

pthread_mutex_t     ugly_gun = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t     bad_gun = PTHREAD_MUTEX_INITIALIZER;

typedef struct  s_cowboy {
    char        *name;
    pthread_t   thread;
}               t_cowboy;

void    *fire_gun(void *data)
{
    t_cowboy    cowboy = *(t_cowboy *)data;

    if (!strcmp(cowboy.name, "Ugly"))
        pthread_mutex_lock(&ugly_gun);
    else
        pthread_mutex_lock(&bad_gun);
    printf("%s: I got my gun!\n", cowboy.name);

    /* Agora, eu quero pegar a arma do outro! */
    if (!strcmp(cowboy.name, "Ugly"))
        pthread_mutex_lock(&bad_gun);
    else
        pthread_mutex_lock(&ugly_gun);

    return (NULL);
}

int main(void)
{
    t_cowboy    ugly =  {"Ugly", 0};
    t_cowboy    bad =   {"Bad", 0};

    pthread_create(&ugly.thread, NULL, fire_gun, &ugly);
    pthread_create(&bad.thread, NULL, fire_gun, &bad);

    pthread_join(ugly.thread, NULL);
    pthread_join(bad.thread, NULL);

    return (EXIT_SUCCESS);
}
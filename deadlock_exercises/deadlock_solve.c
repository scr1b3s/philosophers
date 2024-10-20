/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadlock_solve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:52:07 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/20 17:52:09 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BOLD_RED "\033[1;31m"
#define RESET_COLOR "\033[0m"

#define CLOCK_EMOJI "\U0001F551"
#define GUN_EMOJI "\U0001F52B"
#define SKULL_EMOJI "\U0001F480"
#define FIRE_EMOJI "\U0001F525"

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

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
    char              *name;
    unsigned long     reaction_time;
    pthread_t         thread;
}               t_cowboy;

void    *fire_gun(void *data)
{
    t_cowboy    cowboy = *(t_cowboy *)data;
    printf("%s reaction time "CLOCK_EMOJI": %lu\n",
    cowboy.name,
    cowboy.reaction_time);
    
    usleep(cowboy.reaction_time);

    if (!strcmp(cowboy.name, "Ugly"))
        pthread_mutex_lock(&ugly_gun);
    else
        pthread_mutex_lock(&bad_gun);
    printf("%s: I got my gun! Time to die!!! "FIRE_EMOJI"\n", cowboy.name);

    /* Agora, eu quero pegar a arma do outro! */
    if (!strcmp(cowboy.name, "Ugly"))
        pthread_mutex_lock(&bad_gun);
    else
        pthread_mutex_lock(&ugly_gun);
    
    printf("%s: I got you! "SKULL_EMOJI"\n", cowboy.name);
    printf("\n");

    exit(EXIT_SUCCESS);
    return (NULL);
}

int main(void)
{
    srand(time(NULL) * getpid());
                        /* name, reaction_time, thread */
    t_cowboy    ugly =  {"Ugly", rand() % 10000, 0};
    t_cowboy    bad =   {"Bad", rand() % 10000, 0};

    pthread_create(&ugly.thread, NULL, fire_gun, &ugly);
    pthread_create(&bad.thread, NULL, fire_gun, &bad);

    pthread_join(ugly.thread, NULL);
    pthread_join(bad.thread, NULL);

    return (EXIT_SUCCESS);
}
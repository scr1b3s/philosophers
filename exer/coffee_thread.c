/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coffee_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:58:18 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/19 18:58:21 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static void    *make_coffee(void *name)
{
    printf("%s is making coffee...\n", (char *)name);
    sleep(5);
    printf("%s is done making coffee! ☕\n", (char *)name);
    return (NULL);
}

int main(void)
{
    /* Primeiro, criamos as variáveis p/ cada thread utilizando o tipo pthread_t. */
    pthread_t   thomas;
    pthread_t   marco;
    pthread_t   tiago;
    pthread_t   joao;

    /* Depois, p/ cada thread, chamamos a função
     * pthread_create, que cria uma nova thread. */
    pthread_create(&thomas, NULL, make_coffee, "Thomas");
    pthread_create(&marco, NULL, make_coffee, "Marco");
    pthread_create(&tiago, NULL, make_coffee, "Tiago");
    pthread_create(&joao, NULL, make_coffee, "João");
    /* O primeiro argumento é o ponteiro/endereço da thread, o segundo argumento são os 
     * atributos da thread, nesse caso NULL... Porque não estamos passando nenhum atributo.
     * 
     * O terceiro argumento é a função que a thread irá executar, nesse caso make_coffee.
     * O quarto argumento é o argumento que a função make_coffee irá receber.
     * Que nesse caso é o nome do barista.
     */

    /* Por fim, chamamos a função pthread_join, que espera a thread terminar. */
    pthread_join(thomas, NULL);
    pthread_join(marco, NULL);
    pthread_join(tiago, NULL);
    pthread_join(joao, NULL);
    /* O primeiro argumento é o ponteiro/endereço da thread, o segundo argumento são os 
     * atributos da thread, nesse caso NULL... Porque não estamos passando nenhum atributo.
     */

    return (0);
}
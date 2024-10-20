/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coffe_thread_indef.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:30:23 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/19 22:30:25 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void    *make_coffee(void *name)
{
    printf("%s is making coffee...\n", (char *)name);
    sleep(45);
    printf("%s is done making coffee! ☕\n", (char *)name);

    return (NULL);
}

int main(int argc, char **argv)
{
    (void)argc;
    pthread_t   baristas[atoi(argv[1])];
    int         i;

    i = 0;
    while (i != atoi(argv[1]))
    {
        pthread_create(&baristas[i], NULL, make_coffee, "The Barista");
        i++;
    }

    i = 0;
    while (i != atoi(argv[1]))
    {
        pthread_join(baristas[i], NULL);
        i++;
    }

    return (0);
}
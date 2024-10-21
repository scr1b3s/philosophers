/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coffe e_mono.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:47:00 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/19 18:52:47 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>

static void    make_coffee(char *name)
{
    printf("%s is making coffee...\n", name);
    sleep(5);
    printf("%s is done making coffee! ☕\n", name);
}

int main(void)
{
    char    *thomas = "Thomas";
    char    *marco = "Marco";
    
    make_coffee(thomas);
    make_coffee(marco);
    
    return (0);
}

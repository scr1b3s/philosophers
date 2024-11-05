/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_manipulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:04:57 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/28 20:04:58 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *
 */

// BOOLS
void    set_bool(t_mtx *mtx, bool *var, bool value)
{
    safe_mutex_handle(mtx, LOCK);
    *var = value;
    safe_mutex_handle(mtx, UNLOCK);
}

bool    get_bool(t_mtx *mtx, bool *var)
{
    bool    value;

    safe_mutex_handle(mtx, LOCK);
    value = *var;
    safe_mutex_handle(mtx, UNLOCK);
    return (value);
}

// LONGS
void    set_long(t_mtx *mtx, long *var, long value)
{
    safe_mutex_handle(mtx, LOCK);
    *var = value;
    safe_mutex_handle(mtx, UNLOCK);
}

long    get_long(t_mtx *mtx, long *var)
{
    long    value;

    safe_mutex_handle(mtx, LOCK);
    value = *var;
    safe_mutex_handle(mtx, UNLOCK);
    return (value);
}

bool    simulation_finisihed(t_table *table)
{
    return (get_bool(&table->table_mtx, &table->end_simulation));
}
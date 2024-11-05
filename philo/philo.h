/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k-maru <scribearm@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:33:30 by k-maru            #+#    #+#             */
/*   Updated: 2024/10/21 00:33:31 by k-maru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>  // mutex: init, destroy, lock, unlock...
						// thread: create, join, detach...
# include <errno.h>    // error handling in mtx
# include <limits.h>   // INT_MAX
# include <stdbool.h>  // bool, true, false, just like it, can comment later.
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <sys/time.h> // gettimeofday -> basic cronometer func.
# include <unistd.h>   // write, usleep

# define DEBUG_MODE 1

typedef enum e_opcode_mtx
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode_mtx;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

typedef enum e_status
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
	FIRST_FORK,
	SECOND_FORK,
}						t_philo_status;

/* Structures.
 *
 * Ex. of Execution: ./ philo 5 800 200 200 [5]
 * In Order: num. of philosophers,
 *           time to die,
 *           time to eat,
 *           time to sleep,
 *           [num. of total meals](optional).
 */

typedef pthread_mutex_t	t_mtx;
typedef struct s_philo	t_philo;

/**
 * Fork
 * @struct s_fork
 * @brief Represents a fork in the dining philosophers problem.
 *
 * @var s_fork::fork
 * The mutex used to lock and unlock the fork.
 *
 * @var s_fork::fork_id
 * The unique identifier for the fork.
 */

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

/**
 * Table
 * @struct s_table
 * @brief Represents the dining table in the dining philosophers problem.
 *
 * @var s_table::num_philos
 * The number of philosophers participating in the simulation.
 *
 * @var s_table::time_to_die
 * The maximum time (in microseconds) a philosopher can go without eating
 * before dying.
 *
 * @var s_table::time_to_eat
 * The time (in microseconds) it takes for a philosopher to eat.
 *
 * @var s_table::time_to_sleep
 * The time (in microseconds) a philosopher spends sleeping.
 *
 * @var s_table::num_meals
 * The number of meals each philosopher must eat. If set to -1,
 * there is no limit.
 *
 * @var s_table::start_time
 * The timestamp (in microseconds) when the simulation starts.
 *
 * @var s_table::end_simulation
 * A boolean flag indicating whether the simulation should end.
 * This can happen if a philosopher dies or all philosophers have eaten enough.
 *
 * @var s_table::philos
 * Pointer to the array of philosophers.
 *
 * @var s_table::forks
 * Pòinter to the array of forks.
 */
typedef struct s_table
{
	int					num_philos;

	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_meals;

	long				start_time;
	bool				end_simulation;

	t_philo				*philos;
	t_fork				*forks;

	bool				all_philos_ready;

	t_mtx				table_mtx;
	t_mtx				write_mtx;
}						t_table;

/**
 * Philosopher
 * @struct s_philo
 * @brief Represents a philosopher in the dining philosophers problem.
 *
 * @var s_philo::id
 * The unique identifier for the philosopher.
 *
 * @var s_philo::meals_count
 * The number of meals the philosopher has eaten.
 *
 * @var s_philo::full
 * A boolean indicating if the philosopher has eaten enough.
 *
 * @var s_philo::last_meal_time
 * The time passed since the philosopher's last meal. If this time exceeds
 * the time to die, the philosopher is considered dead. The time is stored
 * in microseconds.
 *
 * @var s_philo::left_fork
 * A pointer to the left fork used by the philosopher.
 *
 * @var s_philo::right_fork
 * A pointer to the right fork used by the philosopher.
 *
 * @var s_philo::thread_id
 * The thread identifier for the philosopher's thread.
 */
struct					s_philo
{
	int					id;

	long				meals_count;
	bool				full;
	long				last_meal_time;

	t_fork				*first_fork;
	t_fork				*second_fork;

	pthread_t			thread_id;

	t_table				*table;

	t_mtx				philo_mtx;
};

/* Functions.
 */

/**
 * Parse Input
 * @brief Parses the input arguments and stores them in the table.
 *
 * @param table A pointer to the table structure.
 * @param ac The number of arguments.
 * @param av The input arguments.
 */
void					parse_input(t_table *table, int ac, char **av);
void					*safe_malloc(size_t bytes);
void					*safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data,
							t_opcode_mtx opcode);
void					*safe_mutex_handle(t_mtx *mtx, t_opcode_mtx opcode);
void					data_init(t_table *table);
void					set_bool(t_mtx *mtx, bool *var, bool value);
bool					get_bool(t_mtx *mtx, bool *var);
void					set_long(t_mtx *mtx, long *var, long value);
long					get_long(t_mtx *mtx, long *var);
bool					simulation_finisihed(t_table *table);
void					wait_all_threads(t_table *table);
long					get_time(t_time_code time_code);
void					precise_usleep(long usec, t_table *table);
void    write_status(t_philo_status status, t_philo *philo, bool debug);
void    dinner_start(t_table *table);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrde-s <andrde-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:04:34 by k-maru            #+#    #+#             */
/*   Updated: 2024/11/27 21:26:47 by andrde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Safe Functions
 * @brief Basic wrapped functions w/ embedded control.
 */

/**
 * safe_malloc
 * @brief Allocates memory and checks if the allocation was successful.
 *
 * @param bytes The number of bytes to allocate.
 */
void	*safe_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
	{
		printf("Error: Malloc failed.\n");
		exit(1);
	}
	return (ptr);
}

/* Threads: */

/**
 * Thread Errors
 * @brief This function initializes the mutex handle and error to threads.
 *
 * This function is responsible for setting up the mutex handle and error
 * handling mechanisms for the threads. It ensures that the mutex is properly
 * initialized and that any errors encountered during the thread operations
 * are appropriately managed.
 *
 * @param mutex_handle A pointer to the mutex handle that will be initialized.
 * @param error A pointer to an error variable that will be used to capture
 *              any errors encountered during thread operations.
 *
 * @return Returns 0 on success, or a non-zero error code on failure.
 */

static void	thread_errors(int stat, t_opcode_mtx opcode)
{
	if (stat != 0)
	{
		if (EAGAIN == stat)
			printf("Insufficient resources to create another thread.\n");
		else if (EPERM == stat)
			printf("Caller does not hold the appropriate permission.\n");
		else if (EINVAL == stat && CREATE == opcode)
			printf("Invalid value specified in attr.\n");
		else if (EINVAL == stat && (JOIN == opcode || DETACH == opcode))
			printf("Value specified by the thread cannot be joined.\n");
		else if (EDEADLK == stat)
			printf("Deadlock detected or val. of \
            thread specifies the calling thread.\n");
		else
			printf("Error: Unknown error.\n");
		exit(1);
	}
	else
		return ;
}

/**
 * Safe Thread Handle
 * @file safe_funcs.c
 * @brief This file contains functions that handle thread operations safely.
 *
 * @param thread A pointer to the thread to be managed.
 * @param foo A function pointer to the thread's start routine.
 * @param data A pointer to the data to be passed to the thread's start routine.
 * @param opcode The operation code indicating the thread operation to perform:
 * - CREATE: Create a new thread.
 * - JOIN: Wait for a thread to terminate.
 * - DETACH: Detach a thread, allowing it to run independently.
 * 
 * @return Returns NULL on success.
 * @return Exits the program on failure.
 */
void	*safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode_mtx opcode)
{
	if (opcode == CREATE)
		thread_errors(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		thread_errors(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		thread_errors(pthread_detach(*thread), opcode);
	else
	{
		printf("Error: Invalid opcode for threads:\
         use <CREATE> <JOIN> <DETACH>\n");
		exit(1);
	}
	return (NULL);
}

/* Mutexes: */

/**
 * Mutex Errors
 * @brief Function that handles mutex errors.
 *
 * @param stat The status of the mutex operation.
 * @param opcode The operation code.
 */

static void	mutex_errors(int stat, t_opcode_mtx opcode)
{
	if (stat != 0)
	{
		if (EINVAL == stat && (LOCK == opcode || UNLOCK == opcode))
			printf("Error: Invalid value specified by mutex.\n");
		else if (EINVAL == stat && (INIT == opcode))
			printf("Error: Invalid value specified by attr.\n");
		else if (EDEADLK == stat)
			printf("Error: A deadlock would occur\
             if the thread blocked waiting for mutex.\n");
		else if (EPERM == stat)
			printf("Error: The current thread does\
             not hold a lock on mutex.\n");
		else if (ENOMEM == stat)
			printf("Error: Insufficient resources to initialize mutex.\n");
		else if (EBUSY == stat)
			printf("Error: The mutex is already locked.\n");
		exit(1);
	}
	else
		return ;
}

/**
 * Safe Mutex Handle
 * @brief Function that handles mutex operations safely w/ support of enum:
 * 	LOCK,
 *	UNLOCK,
 *	INIT,
 *	DESTROY,
 */
void	*safe_mutex_handle(t_mtx *mtx, t_opcode_mtx opcode)
{
	if (opcode == LOCK)
		mutex_errors(pthread_mutex_lock(mtx), opcode);
	else if (opcode == UNLOCK)
		mutex_errors(pthread_mutex_unlock(mtx), opcode);
	else if (opcode == INIT)
		mutex_errors(pthread_mutex_init(mtx, NULL), opcode);
	else if (opcode == DESTROY)
		mutex_errors(pthread_mutex_destroy(mtx), opcode);
	else
	{
		printf("Error: Invalid opcode.\n");
		exit(1);
	}
	return (NULL);
}

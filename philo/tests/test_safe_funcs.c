#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/redirect.h>

#include "../philo.h"
#include <stdint.h>
#include <limits.h>
#include <bits/local_lim.h>
#include "../safe_funcs.c"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

TestSuite(safe_funcs_suite, .init = redirect_all_std);

Test(safe_funcs_suite, test_safe_malloc_success) {
    cr_log_info("Testing safe_malloc with valid input");
    void *ptr = safe_malloc(100);
    cr_assert_not_null(ptr, "Expected non-null pointer");
    free(ptr);
}

Test(safe_funcs_suite, test_safe_malloc_failure, .exit_code = 1) {
    cr_log_info("Testing safe_malloc with invalid input (simulate failure)");
    // Simulate malloc failure by setting a very large size
    safe_malloc(SIZE_MAX);
}

Test(safe_funcs_suite, test_safe_thread_handle_create_success) {
    cr_log_info("Testing safe_thread_handle with CREATE opcode");
    pthread_t thread;
    void *thread_func(void *arg) {
        return NULL;
    }
    int ret = pthread_create(&thread, NULL, thread_func, NULL);
    cr_log_info("pthread_create returned %d", ret);
    cr_assert_eq(ret, 0, "Expected pthread_create to succeed, but got %d", ret);
    safe_thread_handle(&thread, thread_func, NULL, CREATE);
    ret = pthread_join(thread, NULL);
    cr_log_info("pthread_join returned %d", ret);
    cr_assert_eq(ret, 0, "Expected pthread_join to succeed, but got %d", ret);
}

Test(safe_funcs_suite, test_safe_thread_handle_create_failure, .exit_code = 1) {
    cr_log_info("Failure: Testing safe_thread_handle with CREATE opcode (simulate failure)");
    pthread_t thread;
    void *thread_func(void *arg) {
        return NULL;
    }

    // Simulate thread creation failure by exhausting system resources
    cr_log_info("Failure: Simulating thread creation failure by exhausting system resources");

    int i = -1;
    while (1) {
        pthread_t temp_thread;
        ++i;
        if (pthread_create(&temp_thread, NULL, thread_func, NULL) != 0) {
            cr_log_info("Failure: pthread_create failed at iteration %d", i);
            break;
        }
    }

    // Expect that the next thread creation will fail
    cr_log_info("Failure: Expecting safe_thread_handle to fail on thread creation after %d iterations", i);
    safe_thread_handle(&thread, thread_func, NULL, CREATE);
}

Test(safe_funcs_suite, test_safe_thread_handle_join_success) {
    cr_log_info("Testing safe_thread_handle with JOIN opcode");
    pthread_t thread;
    void *thread_func(void *arg) {
        return NULL;
    }
    pthread_create(&thread, NULL, thread_func, NULL);
    safe_thread_handle(&thread, NULL, NULL, JOIN);
}

Test(safe_funcs_suite, test_safe_thread_handle_detach_success, .exit_code = 0) {
    cr_log_info("Testing safe_thread_handle with DETACH opcode");
    pthread_t thread;
    void *thread_func(void *arg) {
        return NULL;
    }
    int ret = pthread_create(&thread, NULL, thread_func, NULL);
    cr_log_info("pthread_create returned %d", ret);
    cr_assert_eq(ret, 0, "Expected pthread_create to succeed, but got %d", ret);
    safe_thread_handle(&thread, NULL, NULL, DETACH);
    // No need to call pthread_detach again
}

Test(safe_funcs_suite, test_safe_mutex_handle_lock_success) {
    cr_log_info("Testing safe_mutex_handle with LOCK opcode");
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    safe_mutex_handle(&mutex, LOCK);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
}

Test(safe_funcs_suite, test_safe_mutex_handle_unlock_success) {
    cr_log_info("Testing safe_mutex_handle with UNLOCK opcode");
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
    safe_mutex_handle(&mutex, UNLOCK);
    pthread_mutex_destroy(&mutex);
}

Test(safe_funcs_suite, test_safe_mutex_handle_init_success) {
    cr_log_info("Testing safe_mutex_handle with INIT opcode");
    pthread_mutex_t mutex;
    safe_mutex_handle(&mutex, INIT);
    pthread_mutex_destroy(&mutex);
}

Test(safe_funcs_suite, test_safe_mutex_handle_destroy_success) {
    cr_log_info("Testing safe_mutex_handle with DESTROY opcode");
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    safe_mutex_handle(&mutex, DESTROY);
}
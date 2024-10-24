#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/redirect.h>
#include <pthread.h>
#include "../safe_funcs.c"
#include "../data_init.c" // Include the source file to test
#include "../philo.h" // Include the header that declares the functions and types

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

TestSuite(data_init_suite, .init = redirect_all_std);

Test(data_init_suite, test_data_init) {
    cr_log_info("Testing data_init function");

    // Setup
    t_table table;
    table.num_philos = 5; // Set a known value for the number of philosophers

    // Call data_init
    data_init(&table);

    // Verify end_simulation is set to false
    cr_assert_eq(table.end_simulation, false, "Expected end_simulation to be false");

    // Verify memory allocation for philos
    cr_assert_not_null(table.philos, "Expected philos to be allocated");
    cr_assert_not_null(table.forks, "Expected forks to be allocated");

    // Verify mutex initialization and fork_id
    for (int i = 0; i < table.num_philos; ++i) {
        int mutex_init_result = pthread_mutex_trylock(&table.forks[i].fork);
        cr_assert_eq(mutex_init_result, 0, "Expected mutex to be initialized and unlocked");
        pthread_mutex_unlock(&table.forks[i].fork); // Clean up by unlocking the mutex
        cr_assert_eq(table.forks[i].fork_id, i, "Expected fork_id to be %d, but got %d", i, table.forks[i].fork_id);
    }

    // Clean up allocated memory
    free(table.philos);
    for (int i = 0; i < table.num_philos; ++i) {
        pthread_mutex_destroy(&table.forks[i].fork);
    }
    free(table.forks);
}

Test(data_init_suite, test_data_init_zero_philos, .exit_code = 1) {
    cr_log_info("Testing data_init function with zero philosophers");

    // Setup
    t_table table;
    table.num_philos = 0; // Set zero philosophers

    // Call data_init
    data_init(&table);

    // Verify end_simulation is set to false
    cr_assert_eq(table.end_simulation, false, "Expected end_simulation to be false");

    // Verify memory allocation for philos and forks
    cr_assert_null(table.philos, "Expected philos to be NULL");
    cr_assert_null(table.forks, "Expected forks to be NULL");
}

Test(data_init_suite, test_data_init_one_philo) {
    cr_log_info("Testing data_init function with one philosopher");

    // Setup
    t_table table;
    table.num_philos = 1; // Set one philosopher

    // Call data_init
    data_init(&table);

    // Verify end_simulation is set to false
    cr_assert_eq(table.end_simulation, false, "Expected end_simulation to be false");

    // Verify memory allocation for philos
    cr_assert_not_null(table.philos, "Expected philos to be allocated");
    cr_assert_not_null(table.forks, "Expected forks to be allocated");

    // Verify mutex initialization and fork_id
    int mutex_init_result = pthread_mutex_trylock(&table.forks[0].fork);
    cr_assert_eq(mutex_init_result, 0, "Expected mutex to be initialized and unlocked");
    pthread_mutex_unlock(&table.forks[0].fork); // Clean up by unlocking the mutex
    cr_assert_eq(table.forks[0].fork_id, 0, "Expected fork_id to be 0, but got %d", table.forks[0].fork_id);

    // Clean up allocated memory
    free(table.philos);
    pthread_mutex_destroy(&table.forks[0].fork);
    free(table.forks);
}

Test(data_init_suite, test_data_init_large_number_of_philos) {
    cr_log_info("Testing data_init function with a large number of philosophers");

    // Setup
    t_table table;
    table.num_philos = 1000; // Set a large number of philosophers

    // Call data_init
    data_init(&table);

    // Verify end_simulation is set to false
    cr_assert_eq(table.end_simulation, false, "Expected end_simulation to be false");

    // Verify memory allocation for philos
    cr_assert_not_null(table.philos, "Expected philos to be allocated");
    cr_assert_not_null(table.forks, "Expected forks to be allocated");

    // Verify mutex initialization and fork_id
    for (int i = 0; i < table.num_philos; ++i) {
        int mutex_init_result = pthread_mutex_trylock(&table.forks[i].fork);
        cr_assert_eq(mutex_init_result, 0, "Expected mutex to be initialized and unlocked");
        pthread_mutex_unlock(&table.forks[i].fork); // Clean up by unlocking the mutex
        cr_assert_eq(table.forks[i].fork_id, i, "Expected fork_id to be %d, but got %d", i, table.forks[i].fork_id);
    }

    // Clean up allocated memory
    free(table.philos);
    for (int i = 0; i < table.num_philos; ++i) {
        pthread_mutex_destroy(&table.forks[i].fork);
    }
    free(table.forks);
}
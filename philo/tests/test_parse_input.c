#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "../parse_input.c"
#include "../philo.h"

TestSuite(parse_input_suite);

Test(parse_input_suite, test_fewer_than_5_arguments) {
    t_table table;
    char *args[] = {"program", "5", "200", "200", "200"};
    int argc = 4;

    cr_log_info("Testing with fewer than 5 arguments");
    int result = parse_input(&table, argc, args);
    cr_assert_eq(result, -1, "Expected return value -1, but got %d", result);
}

Test(parse_input_suite, test_more_than_6_arguments) {
    t_table table;
    char *args[] = {"program", "5", "200", "200", "200", "5", "extra"};
    int argc = 7;

    cr_log_info("Testing with more than 6 arguments");
    int result = parse_input(&table, argc, args);
    cr_assert_eq(result, -1, "Expected return value -1, but got %d", result);
}

Test(parse_input_suite, test_valid_input) {
    t_table table;
    char *args[] = {"program", "5", "200", "200", "200"};
    int argc = 5;

    cr_log_info("Testing with valid input");
    int result = parse_input(&table, argc, args);
    cr_assert_eq(result, 0, "Expected return value 0, but got %d", result);
    cr_assert_eq(table.num_philos, 5, "Expected 5 philosophers, but got %ld", table.num_philos);
    cr_assert_eq(table.time_to_die, 200000, "Expected time_to_die 200000, but got %ld", table.time_to_die);
    cr_assert_eq(table.time_to_eat, 200000, "Expected time_to_eat 200000, but got %ld", table.time_to_eat);
    cr_assert_eq(table.time_to_sleep, 200000, "Expected time_to_sleep 200000, but got %ld", table.time_to_sleep);
    cr_assert_eq(table.num_meals, -1, "Expected num_meals -1, but got %ld", table.num_meals);
}

Test(parse_input_suite, test_negative_philosophers) {
    t_table table;
    char *args[] = {"program", "-5", "200", "200", "200"};
    int argc = 5;

    cr_log_info("Testing with negative number of philosophers");
    int result = parse_input(&table, argc, args);
    cr_assert_eq(result, -1, "Expected return value -1, but got %d", result);
}

Test(parse_input_suite, test_timestamps_less_than_60ms) {
    t_table table;
    char *args[] = {"program", "5", "50", "50", "50"};
    int argc = 5;

    cr_log_info("Testing with timestamps less than 60ms");
    int result = parse_input(&table, argc, args);
    cr_assert_eq(result, -1, "Expected return value -1, but got %d", result);
}

Test(parse_input_suite, test_philosophers_over_INT_MAX) {
    t_table table;
    char *args[] = {"program", "2147483648", "200", "200", "200"};
    int argc = 5;

    cr_log_info("Testing with number of philosophers over INT_MAX");
    int result = parse_input(&table, argc, args);
    cr_assert_eq(result, -1, "Expected return value -1, but got %d", result);
}

Test(parse_input_suite, test_valid_input_without_optional_meals) {
    t_table table;
    char *args[] = {"program", "5", "200", "200", "200"};
    int argc = 5;

    cr_log_info("Testing with valid input but without optional meals argument");
    int result = parse_input(&table, argc, args);
    cr_assert_eq(result, 0, "Expected return value 0, but got %d", result);
    cr_assert_eq(table.num_meals, -1, "Expected num_meals -1, but got %ld", table.num_meals);
}
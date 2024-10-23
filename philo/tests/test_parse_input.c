#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/redirect.h>
#include "../parse_input.c"
#include "../philo.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

TestSuite(parse_input_suite, .init = redirect_all_std);

Test(parse_input_suite, test_fewer_than_5_arguments, .exit_code = 1) {
    t_table table;
    char *args[] = {"program", "5", "200", "200", "200"};
    int argc = 4;

    cr_log_info("Testing with fewer than 5 arguments, should return 1.");
    parse_input(&table, argc, args);
}

Test(parse_input_suite, test_more_than_6_arguments, .exit_code = 1) {
    t_table table;
    char *args[] = {"program", "5", "200", "200", "200", "5", "extra"};
    int argc = 7;

    cr_log_info("Testing with more than 6 arguments, should return 1.");
    parse_input(&table, argc, args);
}

Test(parse_input_suite, test_negative_philosophers, .exit_code = 1) {
    t_table table;
    char *args[] = {"program", "-5", "200", "200", "200"};
    int argc = 5;

    cr_log_info("Testing with negative number of philosophers, should return 1.");
    parse_input(&table, argc, args);
}

Test(parse_input_suite, test_timestamps_less_than_60ms, .exit_code = 1) {
    t_table table;
    char *args[] = {"program", "5", "50", "50", "50"};
    int argc = 5;

    cr_log_info("Testing with timestamps less than 60ms, should return 1.");
    parse_input(&table, argc, args);
}

Test(parse_input_suite, test_philosophers_over_INT_MAX, .exit_code = 1) {
    t_table table;
    char *args[] = {"program", "2147483648", "200", "200", "200"};
    int argc = 5;

    cr_log_info("Testing with number of philosophers over INT_MAX, should return 1.");
    parse_input(&table, argc, args);
}

Test(parse_input, test_valid_inputs_with_meals) {
    t_table table;
    char *args[] = {"program", "5", "200", "200", "200", "5"};
    int argc = 6;

    cr_log_info("Testing with valid input, including num. of meals");
    parse_input(&table, argc, args);
    cr_assert_eq(table.num_philos, 5, "Expected 5 philosophers, but got %d", table.num_philos);
    cr_assert_eq(table.time_to_die, 200000, "Expected time_to_die 200000, but got %d", table.time_to_die);
    cr_assert_eq(table.time_to_eat, 200000, "Expected time_to_eat 200000, but got %d", table.time_to_eat);
    cr_assert_eq(table.time_to_sleep, 200000, "Expected time_to_sleep 200000, but got %d", table.time_to_sleep);
    cr_assert_eq(table.num_meals, 5, "Expected num_meals 5, but got %d", table.num_meals);
}

Test(parse_input, test_valid_inputs_without_meals){
    t_table table;
    char *args[] = {"program", "5", "200", "200", "200"};
    int argc = 5;

    cr_log_info("Testing with valid input, but without optional meals argument");
    parse_input(&table, argc, args);
    cr_assert_eq(table.num_philos, 5, "Expected 5 philosophers, but got %d", table.num_philos);
    cr_assert_eq(table.time_to_die, 200000, "Expected time_to_die 200000, but got %d", table.time_to_die);
    cr_assert_eq(table.time_to_eat, 200000, "Expected time_to_eat 200000, but got %d", table.time_to_eat);
    cr_assert_eq(table.time_to_sleep, 200000, "Expected time_to_sleep 200000, but got %d", table.time_to_sleep);
    cr_assert_eq(table.num_meals, -1, "Expected num_meals -1, but got %d", table.num_meals);
}

Test(parse_input, test_valid_inputs){
    t_table table;
    char *args[] = {"program", "5", "200", "200", "200"};
    int argc = 5;

    cr_log_info("Testing with valid input, including num. of meals");
    parse_input(&table, argc, args);
    cr_assert_eq(table.time_to_die, 200000, "Expected time to die 200000, but got %d", table.num_meals);
}

Test(parse_input, test_valid_input_without_optional_meals) {
    t_table table;
    char *args[] = {"program", "5", "200", "200", "200"};
    int argc = 5;

    cr_log_info("Testing with valid input but without optional meals argument");
    parse_input(&table, argc, args);
    cr_assert_eq(table.num_meals, -1, "Expected num_meals -1, but got %d", table.num_meals);
}

Test(parse_input, test_valid_input) {
    t_table table;
    char *args[] = {"program", "2", "600", "700", "100"};
    int argc = 5;

    cr_log_info("Testing with valid input");
    parse_input(&table, argc, args);
    cr_assert_eq(table.num_philos, 2, "Expected 2 philosophers, but got %d", table.num_philos);
    cr_assert_eq(table.time_to_die, 600000, "Expected time_to_die 600000, but got %d", table.time_to_die);
    cr_assert_eq(table.time_to_eat, 700000, "Expected time_to_eat 700000, but got %d", table.time_to_eat);
    cr_assert_eq(table.time_to_sleep, 100000, "Expected time_to_sleep 100000, but got %d", table.time_to_sleep);
    cr_assert_eq(table.num_meals, -1, "Expected num_meals -1, but got %d", table.num_meals);
}
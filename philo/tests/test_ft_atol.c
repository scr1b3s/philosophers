#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "../philo.h"
#include "../parse_input.c" // Include the source file to test

Test(ft_atol, positive_number) {
    cr_log_info("Test: Convert a simple positive number\n");
    long result = ft_atol("12345");
    cr_assert_eq(result, 12345, "Expected 12345, but got %ld", result);
}

Test(ft_atol, negative_number) {
    cr_log_info("Test: Convert a simple negative number (should fail)\n");
    long result = ft_atol("-12345");
    cr_assert_eq(result, -1, "Expected -1 for invalid input, but got %ld", result);
}

Test(ft_atol, leading_spaces) {
    cr_log_info("Test: Convert a number with leading spaces\n");
    long result = ft_atol("   12345");
    cr_assert_eq(result, 12345, "Expected 12345, but got %ld", result);
}

Test(ft_atol, leading_plus_sign) {
    cr_log_info("Test: Convert a number with leading plus sign\n");
    long result = ft_atol("+12345");
    cr_assert_eq(result, 12345, "Expected 12345, but got %ld", result);
}

Test(ft_atol, leading_minus_sign) {
    cr_log_info("Test: Convert a number with leading minus sign (should fail)\n");
    long result = ft_atol("-12345");
    cr_assert_eq(result, -1, "Expected -1 for invalid input, but got %ld", result);
}

Test(ft_atol, mixed_spaces_and_tabs) {
    cr_log_info("Test: Convert a number with mixed spaces and tabs\n");
    long result = ft_atol(" \t\n 12345");
    cr_assert_eq(result, 12345, "Expected 12345, but got %ld", result);
}

Test(ft_atol, exceeds_int_max) {
    cr_log_info("Test: Convert a number that exceeds INT_MAX (should fail)\n");
    long result = ft_atol("9223372036854775807");
    cr_assert_eq(result, -1, "Expected -1 for overflow, but got %ld", result);
}

Test(ft_atol, zero) {
    cr_log_info("Test: Convert a number that is zero\n");
    long result = ft_atol("0");
    cr_assert_eq(result, 0, "Expected 0, but got %ld", result);
}

Test(ft_atol, empty_string) {
    cr_log_info("Test: Convert an empty string\n");
    long result = ft_atol("");
    cr_assert_eq(result, 0, "Expected 0 for empty string, but got %ld", result);
}

Test(ft_atol, non_numeric_characters) {
    cr_log_info("Test: Convert a string with non-numeric characters\n");
    long result = ft_atol("123abc");
    cr_assert_eq(result, 123, "Expected 123, but got %ld", result);
}

Test(ft_atol, ten_digit_number_exceeds_int_max) {
    cr_log_info("Test: Convert a 10-digit number that exceeds INT_MAX (should fail)\n");
    long result = ft_atol("2147483648"); // INT_MAX is 2147483647
    cr_assert_eq(result, -1, "Expected -1 for overflow, but got %ld", result);
}

Test(ft_atol, ten_digit_number_with_leading_spaces_exceeds_int_max) {
    cr_log_info("Test: Convert a 10-digit number with leading spaces that exceeds INT_MAX (should fail)\n");
    long result = ft_atol("2147483649"); // INT_MAX is 2147483647
    cr_assert_eq(result, -1, "Expected -1 for overflow, but got %ld", result);
}
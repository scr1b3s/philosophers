#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "../parse_input.c" // Include the source file to test

Test(ft_atol, positive_number) {
    cr_log_info("Test: Convert a simple positive number\n");
    cr_assert_eq(ft_atol("12345"), 12345);
}

Test(ft_atol, negative_number) {
    cr_log_info("Test: Convert a simple negative number (should fail)\n");
    cr_assert_eq(ft_atol("-12345"), -1);
}

Test(ft_atol, leading_spaces) {
    cr_log_info("Test: Convert a number with leading spaces\n");
    cr_assert_eq(ft_atol("   12345"), 12345);
}

Test(ft_atol, leading_plus_sign) {
    cr_log_info("Test: Convert a number with leading plus sign\n");
    cr_assert_eq(ft_atol("+12345"), 12345);
}

Test(ft_atol, leading_minus_sign) {
    cr_log_info("Test: Convert a number with leading minus sign (should fail)\n");
    cr_assert_eq(ft_atol("-12345"), -1);
}

Test(ft_atol, mixed_spaces_and_tabs) {
    cr_log_info("Test: Convert a number with mixed spaces and tabs\n");
    cr_assert_eq(ft_atol(" \t\n 12345"), 12345);
}

Test(ft_atol, exceeds_int_max) {
    cr_log_info("Test: Convert a number that exceeds INT_MAX (should fail)\n");
    cr_assert_eq(ft_atol("9223372036854775807"), -1);
}

Test(ft_atol, zero) {
    cr_log_info("Test: Convert a number that is zero\n");
    cr_assert_eq(ft_atol("0"), 0);
}

Test(ft_atol, empty_string) {
    cr_log_info("Test: Convert an empty string\n");
    cr_assert_eq(ft_atol(""), 0);
}

Test(ft_atol, non_numeric_characters) {
    cr_log_info("Test: Convert a string with non-numeric characters\n");
    cr_assert_eq(ft_atol("123abc"), 123);
}
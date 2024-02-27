#ifndef UNIVERSAL_CONVERT_H
#define UNIVERSAL_CONVERT_H

#include <math.h>
#include <stdio.h>
#include <string.h>
#define ALPHABET "NIVXLCDM"

int convert_roman(char *str);
void exception_print();
int check_nulla(char *str);
void output_digit(int res);
void output_str(char *res);
int data_validation(char *str);
void convert_digit(int num, char *res);
int check_result(char *input_str, char *expected_str);
int convert_small_digits(char *str, int num, char *capacity,
                         char *next_capacity, int position);

#endif
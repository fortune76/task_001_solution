#include "roman_to_arabic.h"

int main() {
  char str[15];
  scanf("%s", str);
  if (data_validation(str)) {
    int num = convert_roman(str);
    char res[15] = {'\0'};
    convert_digit(num, res);
    if (check_result(str, res)) {
      output_digit(num);
    } else {
      exception_print();
    }
  } else {
    exception_print();
  }
  return 0;
}

int convert_roman(char *str) {
  int len = strlen(str);
  int sum = 0;
  int i = 0;
  while (i < len) {
    if (str[i] == 'M') {
      sum += 1000;
    } else if (str[i] == 'D') {
      sum += 500;
    } else if (str[i] == 'C') {
      if (str[i + 1] != 'D' && str[i + 1] != 'M') {
        sum += 100;
      } else {
        sum -= 100;
      }
    } else if (str[i] == 'L') {
      sum += 50;
    } else if (str[i] == 'X') {
      if (str[i + 1] != 'C' && str[i + 1] != 'L') {
        sum += 10;
      } else {
        sum -= 10;
      }
    } else if (str[i] == 'V') {
      sum += 5;
    } else if (str[i] == 'I') {
      if (str[i + 1] != 'V' && str[i + 1] != 'X') {
        sum += 1;
      } else {
        sum -= 1;
      }
    }
    i++;
  }
  return sum;
}

int data_validation(char *str) {
  int len = strlen(str);
  int alpha_len = strlen(ALPHABET);
  int counter = 0;
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < alpha_len; j++) {
      if (str[i] == ALPHABET[j]) {
        counter++;
      }
    }
    if (counter == 0) {
      break;
    }
  }
  return counter;
}

// int roman_validation(char *str) {
//   char *i_str = strstr(str, "IIII"), *v_str = strstr(str, "VV");
//   char *x_str = strstr(str, "XXXX"), *l_str = strstr(str, "LL");
//   char *c_str = strstr(str, "CCCC"), *d_str = strstr(str, "DD");
//   int len = strlen(str), counter = 0;
//   for (int i = 0; i < len; i++) {
//     if (i_str || v_str || x_str || l_str || c_str || d_str) {
//       counter++;
//       break;
//     } else if ((counter == 0 && i > 0 && str[i] == 'M' && str[i - 1] != 'C' &&
//                 str[i - 1] != 'M') ||
//                (i > 2 && str[i] == 'M' && strlen(strchr(str, 'C')) != (size_t)(len - i + 1))) {
//       counter++;
//       fprintf(stdout, "1");
//     } else if ((counter == 0 && i > 0 && str[i] == 'D' && str[i - 1] != 'C' &&
//                 str[i - 1] != 'M') ||
//                (i > 2 && str[i] == 'D' && strlen(strchr(str, 'C')) != (size_t)(len - i + 1))) {
//       counter++;
//       fprintf(stdout, "2");
//     } else if ((counter == 0 && i > 0 && str[i] == 'C' && str[i - 1] != 'X' &&
//                 str[i - 1] != 'M' && str[i - 1] != 'D' && str[i - 1] != 'C') ||
//                ((i > 2 && str[i] == 'C' && strlen(strchr(str, 'X')) != (size_t)(len - i + 1)))) {
//       counter++;
//       fprintf(stdout, "3");
//     } else if ((counter == 0 && i > 0 && str[i] == 'L' && str[i - 1] != 'X' &&
//                 str[i - 1] != 'M' && str[i - 1] != 'D' && str[i - 1] != 'C') ||
//                (i > 2 && str[i] == 'L' && strlen(strchr(str, 'X')) != (size_t)(len - i + 1))) {
//       counter++;
//       fprintf(stdout, "4");
//     } else if ((counter == 0 && i > 0 && str[i] == 'X' && str[i - 1] != 'I' &&
//                 str[i - 1] != 'M' && str[i - 1] != 'D' && str[i - 1] != 'C' &&
//                 str[i - 1] != 'L' && str[i - 1] != 'X') ||
//                (i > 2 && str[i] == 'X' && strlen(strchr(str, 'I')) != (size_t)(len - i + 1))) {
//       counter++;
//       fprintf(stdout, "5");
//     } else if ((counter == 0 && i > 0 && str[i] == 'V' && str[i - 1] != 'I' &&
//                 str[i - 1] != 'M' && str[i - 1] != 'D' && str[i - 1] != 'C' &&
//                 str[i - 1] != 'L' && str[i - 1] != 'X') ||
//                (str[i - 2] == 'V' && str[i] == 'V')) {
//       counter++;
//       fprintf(stdout, "6");
//     }
//   }
//   return counter;
// }

void exception_print() { fprintf(stderr, "Puck you, Verter!"); }
void output_digit(int res) { fprintf(stdout, "%d", res); }

// (i > 0 && str[i] == 'M' && str[i - 1] != 'M' &&
//                 strlen(strchr(str, 'C')) != (size_t)i - 1 && str[i - 1] != 'C'))

void convert_digit(int num, char *res) {
  char *thousands = "M";
  char *hungreds = "CD";
  char *dec = "XL";
  char *nums = "IV";
  int counter = 0;
  if (num == 0) {
      strcat(res, "N");
      return;
    }
  for (int i = 3; i > -1; i--) {
    int tmp = num / pow(10, i);
    if (tmp == 0) { continue; }
    if (i == 3) {
      for (int k = 0; k < tmp; k++) {
        strcat(res, thousands);
        counter++;
      }
    } else if (i == 2) {
      counter = convert_small_digits(res, tmp, hungreds, thousands, counter);
    } else if (i == 1) {
      counter = convert_small_digits(res, tmp, dec, hungreds, counter);
    } else if (i == 0) {
      counter = convert_small_digits(res, tmp, nums, dec, counter);
    }
    num -= tmp * pow(10, i);
  }
}

int convert_small_digits(char *str, int num, char *capacity,
                           char *next_capacity, int position) {
  int counter = position;
  if (num >= 1 && num <= 3) {
    for (int k = 0; k < num; k++) {
      str[counter] = capacity[0];
      counter++;
    }
  } else if (num == 4) {
    str[counter] = capacity[0];
    counter++;
    str[counter] = capacity[1];
    counter++;
  } else if (5 <= num && num <= 8) {
    str[counter] = capacity[1];
    counter++;
    for (int k = 0; k < num - 5; k++) {
      str[counter] = capacity[0];
      counter++;
    }
  } else if (num == 9) {
    str[counter] = capacity[0];
    counter++;
    str[counter] = next_capacity[0];
    counter++;
  }
  return counter;
}

int check_result(char *input_str, char *expected_str) {
  int input_len = strlen(input_str);
  int expected_len = strlen(expected_str);
  int result = 1;
  if (input_len == expected_len) {
    for (int i = 0; i < input_len; i++) {
      if (input_str[i] != expected_str[i]) {
        result--;
        break;
      }
    }
  } else {
    result--;
  }
  return result;
}
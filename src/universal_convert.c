#include "universal_convert.h"

int main() {
  int menu = 0;
  char ch;
  if (scanf("%d%c", &menu, &ch) == 2 && ch == '\n') {
    switch (menu) {
    case 1:
      char str[15];
      scanf("%s", str);
      if (check_nulla(str)) {
        output_digit(0);
      } else if (data_validation(str)) {
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
      break;
    case 2:
      int num = 0;
      if (scanf("%d%c", &num, &ch) == 2 && ch == '\n') {
        char res[15] = {'\0'};
        convert_digit(num, res);
        output_str(res);
      } else {
        exception_print();
      }
      break;

    default:
      exception_print();
      break;
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

void exception_print() {
  fprintf(stderr, "Puck you, Verter!");
  exit(EXIT_FAILURE);
}
void output_digit(int res) { printf("%d", res); }
void output_str(char *res) { printf("%s", res); }

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
    if (tmp == 0) {
      continue;
    }
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

int check_nulla(char *str) {
  int res = 0;
  if (strcmp(str, "nulla") == 0 || strcmp(str, "nihil") == 0 || strcmp(str, "N") == 0) {
    res++;
  }
  return res;
}
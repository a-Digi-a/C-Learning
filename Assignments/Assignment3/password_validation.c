#include <stdio.h>

int check_password_strength(char password[]) {
  // declare variables to check state
  char num_check = 0;
  char length_check = 0;
  char special_char_check = 0;
  char lowercase_check = 0;
  char uppercase_check = 0;

  // loop over each character in the string until it hits the string terminator
  for (int i = 0; password[i] != '\0'; i++) {
    // These if statements check what type of character it is, if two characters
    // are of the same type it doesnt matter as we are just setting the variable
    // to 1 multiple times
    if (password[i] >= '0' && password[i] <= '9')
      num_check = 1;
    else if (password[i] >= 'A' && password[i] <= 'Z')
      uppercase_check = 1;
    else if (password[i] >= 'a' && password[i] <= 'z')
      lowercase_check = 1;
    // use ASCII character codes for the special characters, looks neater
    else if ((password[i] >= 33 && password[i] <= 47) ||
             (password[i] >= 58 && password[i] <= 64) ||
             (password[i] >= 91 && password[i] <= 96) ||
             (password[i] >= 123 && password[i] <= 126))
      special_char_check = 1;
    // if its not any of these there is a not permitted character such as a
    // space
    else
      return 0;

    if (i == 7)
      length_check = 1;
  }

  if (num_check && length_check && special_char_check && lowercase_check &&
      uppercase_check == 1) {
    return 1;
  }
  return 0;
}

int main() {
  char str[] = "*hK5p3ei";
  int password_strength = check_password_strength(str);
  printf("%i\n", password_strength);
}

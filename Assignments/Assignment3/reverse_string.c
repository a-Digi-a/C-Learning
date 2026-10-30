#include <stdio.h>
#include <string.h>

void reverseString(char *text) {
  // get length of string
  size_t len = strlen(text);
  // if the string is empty we dont need to do anything
  if (len == 0)
    return;

  // make pointers to the start and end of the text
  char *start = text;
  char *end = text + len - 1;

  // loop over the string swapping the pairs of characters on either end of the
  // string, moving towards the centre. Stop looping when start doesnt equal end
  // (they go past eachother or they meet at the middle character)
  while (start < end) {
    char temp = *start;
    *start = *end;
    *end = temp;
    start++;
    end--;
  }
}

int main() {
  char string[] = "Hello World";
  for (int i = 0; i < strlen(string); i++) {
    printf("%c", string[i]);
  }
  reverseString(string);
  printf("\n");
  for (int i = 0; i < strlen(string); i++) {
    printf("%c", string[i]);
  }
  printf("\n");
}

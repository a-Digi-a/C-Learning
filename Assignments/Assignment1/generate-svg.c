#include <stdio.h>

void print_svg() {
  int bar_fill_percentage = 43;
  int bar_fill_width = 200 * (bar_fill_percentage * 0.01);
  printf("<svg width=\"250\" height=\"100\" "
         "xmlns=\"http://www.w3.org/2000/svg\">\n");
  printf("    <rect width=\"250\" height=\"100\" x=\"0\" y=\"0\" "
         "fill=\"#282828\"></rect>\n");
  printf("    <rect width=\"200\" height=\"30\" x=\"25\" y=\"35\" rx=\"5\" "
         "ry=\"5\" fill=\"grey\"></rect>\n");
  printf("    <rect width=\"%i\" height=\"30\" x=\"25\" y=\"35\" rx=\"5\" "
         "ry=\"5\" fill=\"red\"></rect>\n",
         bar_fill_width);
  printf("    <text x=\"72\" y=\"20\" font-size=\"16\" font-weight=\"bold\" "
         "fill=\"white\">Signal Level</text>\n");
  printf("    <text x=\"108\" y=\"88\" font-size=\"16\" "
         "fill=\"white\">%i%%</text>\n",
         bar_fill_percentage);
  printf("</svg>\n");
};

int main() { print_svg(); }

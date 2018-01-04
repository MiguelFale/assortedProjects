#include "print.h"

int main ( void ) {

  int num = 0xFFFFFFFE;

  num = num -2;
  print_values(num);
  print_bin(num);

  return 0;
} /* end main */

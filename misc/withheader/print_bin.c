#include <stdio.h>
#include "print.h"

void print_bin (int num) {

  int i;

/* vamos começar a imprimir pelo bit 31 */

  for ( i = 31; i >= 0; i-- ) {
    printf ( "%d", (num >> i) & 1 );
  }
  printf ( "\n" );

} /* end print_bin */

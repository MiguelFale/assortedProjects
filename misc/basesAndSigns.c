/* 43556 */
/* fc43556@alunos.fc.ul.pt */

#include <stdio.h>

void binary(int n) {
  int c,k;

for (c = 31; c >= 0; c--)
  {
    k = n >> c;
 
    if (k & 1)
      printf("1");
    else
      printf("0");
  }
 
  printf("\n");
}

int main ( void ) {
  int num;

  num = 0xFFFFFFFE;

  /*2 is 0..010; not(x) + 1 = 111..101+1 = 1...110*/
  printf ( "Valor Hexadecimal: %x; Octal: %o; Decimal: %d; Misterio: %u.\n", num, num, num, num);
  binary(num);

  return 0;

} /* end main */

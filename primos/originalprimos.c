/** 
 *  Primeiro trabalho de Prog1 12-13
 *  Autores: 
 *  Adrian Vilsmaier     43546
 *  Miguel Amorim Fale   43556
 */

#include <stdio.h>

/* prototipos de funcoes definidas pelo programador */
void menu ( void );
int ehPrimo ( int n );
int contaPrimos ( int n );
int maiorPrimo ( int n );
void listaGemeos ( int n );

/* funcao main inicia a execucao do programa */
int main ( void )
{
  int numero; /* inteiro dado pelo utilizador */
  int opc = 1; /* opcao a executar */

  printf ( "Bemvindo ao programa dos numeros primos\n" );

  /* Ciclo de execucao da opc, escrita do menu e leitura de nova opc 
     ate que o valor escolhido seja 0 */
  do {
    /* Processar opcao */
    switch ( opc ) {
       /* opcao 1 */
       /* permite introduzir um novo numero */
       case 1:
       	 printf ( "Numero? " );
         scanf ( "%d", &numero );
         break;

       /* opcao 2 */
       /* permite averiguar se o numero introduzido eh primo */
       case 2:
	 printf ( "Resposta: ");

	 /* se o valor retornado for 1 */
	 if ( ehPrimo ( numero ) == 1 ) 
	   printf ( "%d eh primo\n", numero );

	 /* caso contrario */
	 else
	   printf ( "%d nao eh primo\n", numero );
         break;

       /* opcao 3 */
       /* permite contar numeros primos ate ao numero
          introduzido inclusive se este for primo */
       case 3:
	 printf ( "Resposta: %d\n", contaPrimos ( numero) );
	 break;

       /* opcao 4 */
       /* permite descobrir o maior primo menor do
          que o numero introduzido */
       case 4:
	 printf ( "Resposta: " );

	 /* se o numero introduzido for 2 */
	 if ( numero == 2 )
	   printf ( "nao existe!\n" );

	 /* caso contrario */
	 else
	   printf ( "%d\n", maiorPrimo ( numero ) );

         break;

       /* opcao 5 */
       /* permite imprimir pares de primos gemeos */
       case 5:
	 printf ( "Resposta: " );

	 /* se o numero introduzido for menor que 5 */
	 if ( numero < 5 )
	   printf ( "nao existe nenhum par de gemeos!\n" );

	 /* caso contrario */
	 else
	   listaGemeos ( numero ); /* imprime lista de gemeos */

         break;

       /* opcoes nao existentes */
       default:
	 printf ( "Opcao nao conhecida\n" );
         break;
    }

    menu (); /* escrever menu */

    printf ( "Opcao? " ); /* o programa esta pronto a ler a opcao */
    scanf ( "%d", &opc ); /* ler numero de opcao */

  } while ( opc != 0 );

  printf( "Fim.\n" );

  return 0; /* o programa termina com sucesso */
} /* fim da funcao main */ 


/*********************************
* Funcao: menu                   *
* Imprime o menu.                *
* Nao ha retorno de valores.     *
*********************************/
void menu ( void )
{
  printf ( "Menu:\n" );
  printf ( "1 - Introduzir novo numero\n" );
  printf ( "2 - Eh primo?\n" );
  printf ( "3 - Contar primos\n" );
  printf ( "4 - Maior primo\n" );
  printf ( "5 - Lista de gemeos\n" );
  printf ( "0 - Terminar\n" );

}/* fim da funcao menu */

/************************************************
* Funcao: ehPrimo                               *
* Verifica se o parametro n eh um numero primo. *
* Retorna 1 se n eh primo e 0 no caso contrario.*
************************************************/
int ehPrimo ( int n )
{
  int contador; /* contador geral que assegura o fim da iteracao */
  int contadordivisores = 0;

  /* Ciclo que testa todos os valores de 1 a n
     inclusive e verifica se sao divisores de n */
  for ( contador = 1; contador <= n; contador++ )
    if ( n % contador == 0 )
      contadordivisores++;

  /* Se o contadordivisores foi incrementado exatamente duas vezes
     entao n eh primo */
  if ( contadordivisores == 2 )
    return 1;

  else
    return 0;

} /* fim da funcao ehPrimo */


/***************************************************
* Funcao: contaPrimos                              *
* Conta todos os numeros primos antes de n.        *
* Retorna o numero de primos menores ou iguais a n.*
***************************************************/
int contaPrimos ( int n )
{
  int contador; /* contador geral que assegura o fim da iteracao */
  int contador_primos = 0;

  /* Ciclo que verifica quantos numeros primos existem
     menores ou iguais a n */
  for ( contador = 1; contador <= n; contador++ )
    if ( ehPrimo ( contador ) == 1 )
      contador_primos++;

  return contador_primos;
} /*fim da funcao contaPrimos*/


/***************************************************
* Funcao: maiorPrimo                               *
* Descobre qual o maior numero primo menor que n.  *
* Retorna o maior numero primo menor que n.        *
***************************************************/
int maiorPrimo (int n)
{
  int contador; /* contador geral que assegura o fim da iteracao */
  int marcador_primo;

  /* Ciclo que verifica se o valor do contador actual
     eh primo e actualiza o marcador */
  for ( contador = 1; contador < n; contador++ )
    if ( ehPrimo ( contador ) == 1 )
      marcador_primo = contador;

  return marcador_primo;

} /*fim da funcao maiorPrimo*/  


/********************************************
* Funcao: listaGemeos                       *
* Imprime a lista de pares de primos gemeos *
* menores ou iguais a n.                    *
* nao ha retorno de valores                 *
*********************************************/
void listaGemeos ( int n )
{
  int contador; /* contador geral que assegura o fim da iteracao */
  int numeroA; /* numero actual */
  int numeroB; /* numero actual subtraido por 2 */

  /* Ciclo que verifica se o valor do contador actual
     eh primo gemeo e imprime a lista de pares gemeos */
  for ( contador = 1; contador <= n; contador++ ) {
    if ( ehPrimo ( contador ) == 1 ) {

      numeroA = contador;
      numeroB = contador - 2;
      if ( ehPrimo ( numeroB ) == 1 )
	printf ( "(%d, %d) ", numeroB, numeroA );
    } /* fim do if */
  } /* fim do for */

  printf ( "\n" );

} /* fim da funcao listaGemeos */
